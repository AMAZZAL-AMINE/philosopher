/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazzal <mamazzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:04:45 by mamazzal          #+#    #+#             */
/*   Updated: 2023/06/02 11:34:48 by mamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_current_time(void)
{
	struct timeval	current_time;
	long long		time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000LL) + (current_time.tv_usec / 1000LL);
	return (time);
}

void	sleep_time(int time, t_philo *philo)
{
	long long	start_time;

	start_time = get_current_time();
	while (get_current_time() < (start_time + time))
	{
		pthread_mutex_lock(&philo->data->print_lock);
		if (philo->data->is_dead == 1)
		{
			pthread_mutex_unlock(&philo->data->print_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data->print_lock);
		usleep(250);
	}
}
