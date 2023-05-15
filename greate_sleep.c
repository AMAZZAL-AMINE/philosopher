/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greate_sleep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazzal <mamazzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 13:31:40 by mamazzal          #+#    #+#             */
/*   Updated: 2023/05/15 17:24:59 by mamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void greate_sleep(int time, s_philo *p_data) {
    (void)p_data;
    long long current_time = get_current_time();
    long long start = current_time;

    while (get_current_time() < (start + time)) {
        usleep(50);
    }
}
