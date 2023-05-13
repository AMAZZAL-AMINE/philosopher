/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazzal <mamazzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 13:23:09 by mamazzal          #+#    #+#             */
/*   Updated: 2023/05/13 22:30:23 by mamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long get_action_time(struct timeval tv) {
	long long time_in_mills = (tv.tv_sec * 1000LL) + ( tv.tv_usec / 1000LL);
	return (get_current_time() - time_in_mills);
}

void printf_actions(char *msg, struct timeval tv, int t_id) {
	printf("%lld\t%d     %s\n", get_action_time(tv), t_id, msg);
}

void print_eat(struct timeval tv, int t_id, s_philo *p_data) {
	gettimeofday(p_data->tv_last_eat, NULL);
	printf("%lld\t%d     is eating\n", get_actiocn_time(tv), t_id);
}