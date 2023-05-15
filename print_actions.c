/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazzal <mamazzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 13:23:09 by mamazzal          #+#    #+#             */
/*   Updated: 2023/05/15 17:57:06 by mamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long get_action_time(struct timeval tv) {
	long long time_in_mills = (tv.tv_sec * 1000LL) + ( tv.tv_usec / 1000LL);
	return (get_current_time() - time_in_mills);
}

void printf_actions(char *msg,  s_philo *p_data) {
	long long c_time = (get_current_time() - p_data->data->start_time);
	int	id = p_data->p_id;
	printf("%lld\t%d     %s\n", c_time, id, msg);
}

void print_eat(int t_id, s_philo *p_data) {
	printf("%lld\t%d     is eating\n", (get_current_time() - p_data->data->start_time), t_id);
}