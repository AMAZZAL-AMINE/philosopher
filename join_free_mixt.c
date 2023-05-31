/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_free_mixt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazzal <mamazzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:47:36 by mamazzal          #+#    #+#             */
/*   Updated: 2023/05/31 15:45:08 by mamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_allocation(t_philo *philo, t_shared_source *source)
{
	free(philo->data->mutex);
	free(source);
	free(philo);
}

int	destry_mutexs(t_philo *philo)
{
	int	count;

	count = 0;
	while (count < philo->data->n_philos)
	{
		if (pthread_mutex_destroy(&philo[count].data->mutex[count]))
			return (1);
		count++;
	}
	return (0);
}

int	join_and_destroy(t_philo *philo)
{
	int	count;

	count = 0;
	if (philo->data->n_philos == 1)
	{
		if (pthread_mutex_destroy(&philo->data->print_lock))
			return (1);
		return (0);
	}
	else
	{
		while (count < philo->data->n_philos)
		{
			if (pthread_join(philo[count].philo, NULL))
				return (1);
			count++;
		}
		if (pthread_mutex_destroy(&philo->data->print_lock))
			return (1);
		if (destry_mutexs(philo))
			return (1);
	}
	return (0);
}
