/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazzal <mamazzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:09:52 by mamazzal          #+#    #+#             */
/*   Updated: 2023/05/23 16:48:41 by mamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int philo_todo(s_philo *philo) {
    pthread_mutex_lock(&philo->data->mutex[philo->left_mutex]);
    print_action("has taken a fork", philo);
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
        sleep_time(philo->data->n_time_sleep);
    }  
    while (philo->data->is_dead != 1)
        philo_todo(philo);
    return ((void *)1);
}