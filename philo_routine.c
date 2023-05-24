/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazzal <mamazzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:09:52 by mamazzal          #+#    #+#             */
/*   Updated: 2023/05/24 21:53:41 by mamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int philo_todo(s_philo *philo) {
    pthread_mutex_lock(&philo->data->mutex[philo->left_mutex]);
    print_action("has taken a fork", philo);
    if ((get_current_time() - philo->last_eat) > philo->data->n_time_die) {
        philo->is_dead = 1;
        philo->data->is_dead = 1;
        pthread_mutex_lock(&philo->data->print_lock);
        printf("%lld %d is died\n", (get_current_time() - philo->created_at), philo->p_id);
        pthread_mutex_unlock(&philo->data->print_lock);
        return 1;
    }
    pthread_mutex_lock(&philo->data->mutex[philo->right_mutex]);
    print_action("has taken a fork", philo);
    philo->last_eat = get_current_time();
    print_action("is eating", philo);
    sleep_time(philo->data->n_time_eat);
    pthread_mutex_unlock(&philo->data->mutex[philo->right_mutex]);
    pthread_mutex_unlock(&philo->data->mutex[philo->left_mutex]);
    print_action("is sleeping", philo);
    sleep_time(philo->data->n_time_sleep);
    print_action("is thinking", philo);
    return 0;
}

void *philo_routine(void *data) {
    s_philo *philo = (s_philo *)data;
    if (philo->p_id % 2 != 0) {
        print_action("is thinking", philo);
        sleep_time(philo->data->n_time_eat);
    }
    while (!philo->data->is_dead) {
        pthread_mutex_lock(&philo->data->mutex[philo->left_mutex]);
        print_action("has taken a fork", philo);
        pthread_mutex_lock(&philo->data->mutex[philo->right_mutex]);
        print_action("has taken a fork", philo);
        print_action("is eating", philo);
        philo->last_eat = get_current_time();
        sleep_time(philo->data->n_time_eat);
        pthread_mutex_unlock(&philo->data->mutex[philo->right_mutex]);
        pthread_mutex_unlock(&philo->data->mutex[philo->left_mutex]);
        print_action("is sleeping", philo);
        sleep_time(philo->data->n_time_sleep);
        print_action("is thinking", philo);
    }
    return ((void *)1);
}
