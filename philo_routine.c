/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazzal <mamazzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:09:52 by mamazzal          #+#    #+#             */
/*   Updated: 2023/05/30 12:48:10 by mamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philo_routine(void *data) {
    s_philo *philo = (s_philo *)data;
    if (philo->p_id % 2 != 0) {
        print_action("is thinking", philo);
        sleep_time(philo->data->n_time_eat);
    }  
    while (1) {
        pthread_mutex_lock(&philo->data->print_lock);
        int is_dead = philo->data->is_dead;
        pthread_mutex_unlock(&philo->data->print_lock);
        if (is_dead == 1 || philo->ichb3a == 1) {
            return ((void *)1);
        }
        pthread_mutex_lock(&philo->data->mutex[philo->left_mutex]);
        print_action("has taken a fork", philo);
        pthread_mutex_lock(&philo->data->mutex[philo->right_mutex]);
        print_action("has taken a fork", philo);
        print_action("is eating", philo);
        pthread_mutex_lock(&philo->data->print_lock);
        philo->last_eat = get_current_time();
        pthread_mutex_unlock(&philo->data->print_lock);
        philo->meals++;
        if (philo->meals >= philo->data->n_must_eat && philo->data->n_must_eat != -1) {
            pthread_mutex_lock(&philo->data->print_lock);
            philo->ichb3a = 1;
            pthread_mutex_unlock(&philo->data->print_lock);
        }
        sleep_time(philo->data->n_time_eat);
        pthread_mutex_unlock(&philo->data->mutex[philo->right_mutex]);
        pthread_mutex_unlock(&philo->data->mutex[philo->left_mutex]);
        pthread_mutex_lock(&philo->data->print_lock);
        pthread_mutex_unlock(&philo->data->print_lock);
        print_action("is sleeping", philo);
        sleep_time(philo->data->n_time_sleep);
        print_action("is thinking", philo);
    }
    return ((void *)1);
}
