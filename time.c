/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazzal <mamazzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:04:45 by mamazzal          #+#    #+#             */
/*   Updated: 2023/05/27 16:55:04 by mamazzal         ###   ########.fr       */
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
    long long start_time = get_current_time();
    while (get_current_time() < (start_time + time)) {
        usleep(250);
    }
}