/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazzal <mamazzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:03:22 by mamazzal          #+#    #+#             */
/*   Updated: 2023/05/17 15:33:01 by mamazzal         ###   ########.fr       */
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

int print_action(char *msg, s_philo *philo) {
    pthread_mutex_lock(&philo->data->print_lock);
    long time = get_current_time() - philo->created_at;
    printf("%ld %d %s\n", time, philo->p_id, msg);
    pthread_mutex_unlock(&philo->data->print_lock);
    return 0;
}

int print_eat(s_philo *philo) {
    pthread_mutex_lock(&philo->data->print_lock);
    long time = get_current_time() - philo->created_at;
    philo->last_eat = get_current_time();
    printf("%ld %d is eating\n", time, philo->p_id);
    pthread_mutex_unlock(&philo->data->print_lock);
    return 0;
}

void *philo_routine(void *data) {
    s_philo *philo = (s_philo *)data;
    while (1) {
        pthread_mutex_t right_mutex = philo->mutex;
        pthread_mutex_t left_mutex = philo->left_mutex;
        print_action("is thinking", philo);
        pthread_mutex_lock(&right_mutex);
        print_action("has taken a fork", philo);
        pthread_mutex_lock(&left_mutex);
        print_action("has taken a fork", philo);
        print_eat(philo);
        sleep_time(philo->data->n_time_eat);
        pthread_mutex_unlock(&left_mutex);
        pthread_mutex_unlock(&right_mutex);
        print_action("is sleeping", philo);
        sleep_time(philo->data->n_time_sleep);
    }
    return NULL;
}

int start_dinner(char **argv, s_philo *philo) {
    philo->data->n_philos = ft_atoi(argv[1]);
    philo->data->n_time_die = ft_atoi(argv[2]);
    philo->data->n_time_eat = ft_atoi(argv[3]);
    philo->data->n_time_sleep = ft_atoi(argv[4]);
    philo->data->start_time = get_current_time();
    pthread_mutex_init(&philo->data->print_lock, NULL);
    pthread_mutex_init(&philo->data->exit_lock, NULL);
    int count = 0;
    //create right mutex
    while (count < philo->data->n_philos) {
        pthread_mutex_init(&philo[count].mutex, NULL);
        count++;
    }

    //create threads
    count = 0;
    while (count < philo->data->n_philos) {
        philo[count].p_id = count + 1;
        philo[count].created_at = get_current_time();
        philo[count].left_mutex = philo[(philo[count].p_id + 1) % philo->data->n_philos].mutex;
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
            if (philo[count].data->n_time_die < (int)(get_current_time() - philo[count].last_eat)) {
                printf("%d died\n", count + 1);
                return 0;
            }
            count++;
        }
        start_dinner(argv, philo);
    }
    return 0;
}