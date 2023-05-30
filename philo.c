/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazzal <mamazzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:03:22 by mamazzal          #+#    #+#             */
/*   Updated: 2023/05/30 13:14:53 by mamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int start_dinner(char **argv, s_philo *philo, int argc) {
    philo->data->is_dead = 0;
    philo->data->n_philos = ft_atoi(argv[1]);
    philo->data->n_time_die = ft_atoi(argv[2]);
    philo->data->n_time_eat = ft_atoi(argv[3]);
    philo->data->n_time_sleep = ft_atoi(argv[4]);
    philo->data->mutex = malloc(sizeof(pthread_mutex_t) * philo->data->n_philos);
    if (argc == 6) {
        philo->data->n_must_eat = ft_atoi(argv[5]) + 1;
    }else {
        philo->data->n_must_eat = -1;
    }
    pthread_mutex_init(&philo->data->print_lock, NULL);
    pthread_mutex_init(&philo->data->exit_lock, NULL);
    
    /**
     * MUTEXS
     */
    int count = 0;
    while (count < philo->data->n_philos) {
        pthread_mutex_init(&philo->data->mutex[count], NULL);
        count++;
    }
    
    /**
     * THREADS
     */
    count = 0;
    
    long long time = get_current_time();
    while (count < philo->data->n_philos) {
        philo[count].created_at = time;
        philo[count].is_dead = 0;
        philo[count].p_id = count + 1;
        philo[count].left_mutex = count;
        philo[count].right_mutex = (count + 1) % philo->data->n_philos;
        philo[count].last_eat = time;
        philo[count].meals = 0;
        philo[count].ichb3a = 0;
        pthread_create(&philo[count].philo, NULL, philo_routine, &philo[count]);
        count++;
    }
    return 0;
}

int check_ichb3a(s_philo *philo)
{
    int count = 0;
    int i = 0;
    while (i < philo->data->n_philos) {
        pthread_mutex_lock(&philo->data->print_lock);
        if (philo[count].ichb3a == 1)
            count++;
        pthread_mutex_unlock(&philo->data->print_lock);
        i++;
    }
    if (count == philo->data->n_philos)
        return 1;
    return 0;
}

int check_is_die(s_philo *philo) {
    int count = 0;
    long long period;
    while (count < philo->data->n_philos) {
        pthread_mutex_lock(&philo->data->print_lock);
        period = get_current_time() - philo[count].last_eat;
        pthread_mutex_unlock(&philo->data->print_lock);
        if (period > philo->data->n_time_die) {
            philo[count].is_dead = 1;
            philo->data->is_dead = 1;
            pthread_mutex_lock(&philo->data->print_lock);
            printf("%lld %d is died\n", (get_current_time() - philo[count].created_at), philo[count].p_id);
            pthread_mutex_unlock(&philo->data->print_lock);
            return 1;
        }
        count++;
    }
    return 0;
}

int main(int argc, char **argv) {
    if (argc < 5 || argc > 6) {
        printf("Error: wrong number of arguments\n");
        return 1;
    }
    if (is_not_numbers(argv + 1)) {
        printf("Error: arguments must be numbers\n");
        return 1;
    }
    if (!niga_tive(ft_atoi(argv[1])) || !niga_tive(ft_atoi(argv[2]))) {
        printf("Error: arguments must be positive numbers\n");
        return 1;
    }
    
    int count = 0;
    s_philo *philo = malloc(sizeof(s_philo) * ft_atoi(argv[1]));
    s_shared_source *source = malloc(sizeof(s_shared_source));
    int n_philo = ft_atoi(argv[1]);
    while (count < n_philo) {
        philo[count].data = source;
        count++;
    }
    start_dinner(argv, philo, argc);
    while (1) {
        if (check_is_die(philo) || check_ichb3a(philo)){
          break;
        }
    }

    count = 0;
    while (count < n_philo) {
        pthread_join(philo[count].philo, NULL);
        count++;
    }
    pthread_mutex_destroy(&philo->data->print_lock);
    count = 0;
    while (count < n_philo) {
        pthread_mutex_destroy(&philo[count].data->mutex[count]);
        count++;
    }
    return 0;
}