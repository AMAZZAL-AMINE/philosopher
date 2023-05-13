/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_philo_time.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazzal <mamazzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 22:30:43 by mamazzal          #+#    #+#             */
/*   Updated: 2023/05/13 22:22:01 by mamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long get_current_time() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
    long long milliseconds = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL);
	return milliseconds;
}

long long time_to_millscnd(struct timeval tv) {
	long long milliseconds = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL);
	return milliseconds; 
}