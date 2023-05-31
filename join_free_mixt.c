/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_free_mixt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazzal <mamazzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:47:36 by mamazzal          #+#    #+#             */
/*   Updated: 2023/05/31 11:33:25 by mamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_allocation(t_philo *philo, t_shared_source *source)
{
	free(philo->data->mutex);
	free(source);
	free(philo);
}

int	join_and_destroy(t_philo *philo)
{
	int	count;

	count = 0;
	if (philo->data->n_philos == 1)
	{
		pthread_mutex_destroy(&philo->data->print_lock);
		pthread_mutex_destroy(&philo[0].data->mutex[0]);
		return (0);
	}
	else
	{
		while (count < philo->data->n_philos)
		{
			pthread_join(philo[count].philo, NULL);
			count++;
		}
		pthread_mutex_destroy(&philo->data->print_lock);
		count = 0;
		while (count < philo->data->n_philos)
		{
			pthread_mutex_destroy(&philo[count].data->mutex[count]);
			count++;
		}
	}
	return (0);
}
