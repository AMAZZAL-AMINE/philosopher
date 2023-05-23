/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazzal <mamazzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:07:51 by mamazzal          #+#    #+#             */
/*   Updated: 2023/05/23 16:27:38 by mamazzal         ###   ########.fr       */
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
