/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazzal <mamazzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:40:52 by mamazzal          #+#    #+#             */
/*   Updated: 2023/05/31 15:39:55 by mamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_shared_data(t_philo *philo, int argc, char **argv)
{
	philo->data->is_dead = 0;
	philo->data->n_philos = ft_atoi(argv[1]);
	philo->data->n_time_die = ft_atoi(argv[2]);
	philo->data->n_time_eat = ft_atoi(argv[3]);
	philo->data->n_time_sleep = ft_atoi(argv[4]);
	philo->data->mutex = malloc(sizeof(pthread_mutex_t) * \
		philo->data->n_philos);
	if (!philo->data->mutex)
		return (1);
	if (argc == 6)
		philo->data->n_must_eat = ft_atoi(argv[5]) + 1;
	else
		philo->data->n_must_eat = -1;
	if (pthread_mutex_init(&philo->data->print_lock, NULL))
		return (1);
	return (0);
}

int	init_mutexs(t_philo *philo)
{
	int	count;

	count = 0;
	while (count < philo->data->n_philos)
	{
		if (pthread_mutex_init(&philo->data->mutex[count], NULL))
			return (1);
		count++;
	}
	return (0);
}

int	init_threads(t_philo *philo)
{
	long long	time;
	int			count;

	count = 0;
	time = get_current_time();
	while (count < philo->data->n_philos)
	{
		philo[count].created_at = time;
		philo[count].is_dead = 0;
		philo[count].p_id = count + 1;
		philo[count].left_mutex = count;
		philo[count].right_mutex = (count + 1) % philo->data->n_philos;
		philo[count].last_eat = time;
		philo[count].meals = 0;
		philo[count].ichb3a = 0;
		if (pthread_create(&philo[count].philo, NULL, \
			philo_routine, &philo[count]))
			return (1);
		count++;
	}
	return (0);
}
