/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazzal <mamazzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:03:22 by mamazzal          #+#    #+#             */
/*   Updated: 2023/05/19 22:38:45 by mamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long get_current_time() {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    long long time = (current_time.tv_sec * 1000LL) + (current_time.tv_usec / 1000LL);
    return time;
}

void sleep_time(int time) {
    long long start_time = get_current_time() + time;
    while (get_current_time() < start_time) {
        usleep(50);
    }
}

void print_action(char *msg, s_philo *philo) {
    long time = get_current_time() - philo->created_at;
    printf("%ld %d %s\n", time, philo->p_id, msg);
}

void print_eat(s_philo *philo) {
    long time = get_current_time() - philo->created_at;
    philo->last_eat = get_current_time();
    printf("%ld %d is eating\n", time, philo->p_id);
    sleep_time(philo->data->n_time_eat);
}

int philo_todo(s_philo *philo) {
    pthread_mutex_lock(&philo->data->mutex[philo->left_mutex]);
    print_action("has taken a fork", philo);
    if (philo->data->n_philos == 1) {
        philo->is_dead = 1;
        return 1;
    }
    pthread_mutex_lock(&philo->data->mutex[philo->right_mutex]);
    print_action("has taken a fork", philo);
    print_eat(philo);
    pthread_mutex_unlock(&philo->data->mutex[philo->right_mutex]);
    pthread_mutex_unlock(&philo->data->mutex[philo->left_mutex]);
    print_action("is sleeping", philo);
    sleep_time(philo->data->n_time_sleep);
    print_action("is thinking", philo);
    if ((get_current_time() - philo->last_eat) > philo->data->n_time_die) {
        philo->is_dead = 1;
        return 1;
    }
    return 0;
}

void *philo_routine(void *data) {
    s_philo *philo = (s_philo *)data;
    if (philo->p_id % 2 != 0) {
        print_action("is thinking", philo);
        sleep_time(philo->data->n_time_eat);
    }
    while (1) {
       if (philo_todo(philo) == 1)
           return ((void *)1);
    }
    return ((void *)0);
}


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
    int count = 0;
    //create right mutex
    while (count < philo->data->n_philos) {
        pthread_mutex_init(&philo->data->mutex[count], NULL);
        count++;
    }

    //create threads
    count = 0;
    while (count < philo->data->n_philos) {
        philo[count].p_id = count + 1;
        philo[count].left_mutex = count;
        philo[count].right_mutex = (count + 1) % philo->data->n_philos;

        philo[count].created_at = get_current_time();
        pthread_create(&philo[count].philo, NULL, philo_routine, &philo[count]);
        count++;
    }

    //join threads
    count = 0;
    while (count < philo->data->n_philos) {
        pthread_join(philo[count].philo, NULL);
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
    while (1) {
        count = 0;
        while (count < philo->data->n_philos) {
            if (philo[count].is_dead == 1) {
                print_action("died", &philo[count]);
                exit(0);
            }
            count++;
        }
        start_dinner(argv, philo);
    }
    return 0;
}