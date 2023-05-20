/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazzal <mamazzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:03:22 by mamazzal          #+#    #+#             */
/*   Updated: 2023/05/20 22:08:52 by mamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int start_dinner(char **argv, s_philo *philo) {
    philo->data->n_philos = ft_atoi(argv[1]);
    philo->data->n_time_die = ft_atoi(argv[2]);
    philo->data->n_time_eat = ft_atoi(argv[3]);
    philo->data->n_time_sleep = ft_atoi(argv[4]);
    philo->data->start_time = get_current_time();
    philo->data->mutex = malloc(sizeof(pthread_mutex_t) * philo->data->n_philos);
    pthread_mutex_init(&philo->data->print_lock, NULL);
    pthread_mutex_init(&philo->data->exit_lock, NULL);
    pthread_mutex_init(&philo->data->lock, NULL);
    
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
    while (count < philo->data->n_philos) {
        philo[count].p_id = count + 1;
        philo[count].left_mutex = count;
        philo[count].right_mutex = (count + 1) % philo->data->n_philos;
        philo[count].last_eat = get_current_time();
        philo[count].created_at = get_current_time();
        philo[count].is_dead = 0;
        pthread_create(&philo[count].philo, NULL, philo_routine, &philo[count]);
        count++;
    }
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 5)
        exit(1);
    int count = 0;
    s_philo *philo = malloc(sizeof(s_philo) * ft_atoi(argv[1]));
    s_shared_source *source = malloc(sizeof(s_shared_source));
    while (count < ft_atoi(argv[1])) {
        philo[count].data = source;
        count++;
    }
     start_dinner(argv, philo);
    while (1) {
        count = 0;
        while (count < philo->data->n_philos) {
            if ((get_current_time() - philo[count].last_eat) > (philo->data->n_time_die)) {
                philo[count].is_dead = 1;
                print_action("died",philo);
                return 1;
            }
            count++;
        }
    }
    count = 0;
    while (count < philo->data->n_philos) {
        pthread_join(philo[count].philo, NULL);
        count++;
    }
    return 0;
}