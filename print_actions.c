/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazzal <mamazzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:07:51 by mamazzal          #+#    #+#             */
/*   Updated: 2023/05/23 15:11:38 by mamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_action(char *msg, s_philo *philo) {
    pthread_mutex_lock(&philo->data->print_lock);
    if (philo->data->is_dead == 0) {
        printf("%lld %d %s\n", get_current_time() - philo->created_at, philo->p_id, msg);
    }
    pthread_mutex_unlock(&philo->data->print_lock);
}

// void print_eat(s_philo *philo) {
//     long time = get_current_time() - philo->created_at;
//     pthread_mutex_lock(&philo->data->print_lock);
//     if (philo->data->is_dead == 0) {
//         philo->last_eat = get_current_time();
//         printf("%ld %d is eating\n", time, philo->p_id);
//     }
//     pthread_mutex_unlock(&philo->data->print_lock);
//     sleep_time(philo->data->n_time_eat);
// }

// void print_died(char *msg, s_philo *philo) {
//     long time = get_current_time() - philo->created_at;
//     pthread_mutex_lock(&philo->data->print_lock);
//     if (philo->data->is_dead == 1) {
//         printf("%ld %d %s\n", time, philo->p_id, msg);
//     }
//     pthread_mutex_unlock(&philo->data->print_lock);
// }
