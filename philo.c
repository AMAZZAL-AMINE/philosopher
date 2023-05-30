/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazzal <mamazzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:03:22 by mamazzal          #+#    #+#             */
/*   Updated: 2023/05/30 19:05:40 by mamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_dinner(char **argv, t_philo *philo, int argc)
{
	init_shared_data(philo, argc, argv);
	init_mutexs(philo);
	init_threads(philo);
	return (0);
}

int	check_ichb3a(t_philo *philo)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (i < philo->data->n_philos)
	{
		pthread_mutex_lock(&philo->data->print_lock);
		if (philo[count].ichb3a == 1)
			count++;
		pthread_mutex_unlock(&philo->data->print_lock);
		i++;
	}
	if (count == philo->data->n_philos)
		return (1);
	return (0);
}

int	check_is_die(t_philo *philo)
{
	long long	period;
	int			count;

	count = 0;
	while (count < philo->data->n_philos)
	{
		pthread_mutex_lock(&philo->data->print_lock);
		period = get_current_time() - philo[count].last_eat;
		pthread_mutex_unlock(&philo->data->print_lock);
		if (period > philo->data->n_time_die)
		{
			philo[count].is_dead = 1;
			philo->data->is_dead = 1;
			pthread_mutex_lock(&philo->data->print_lock);
			printf("%lld %d is died\n", (get_current_time() - \
				philo[count].created_at), philo[count].p_id);
			pthread_mutex_unlock(&philo->data->print_lock);
			return (1);
		}
		count++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_shared_source	*source;
	int				count;
	int				n_philo;
	t_philo			*philo;

	if (is_error(argc, argv) == 1 || (argc > 6 && argc < 5))
		return (1);
	count = 0;
	philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	source = malloc(sizeof(t_shared_source));
	n_philo = ft_atoi(argv[1]);
	while (count < n_philo)
	{
		philo[count].data = source;
		count++;
	}
	start_dinner(argv, philo, argc);
	while (1)
		if (check_is_die(philo) || check_ichb3a(philo))
			break ;
	if (join_and_destroy(philo) == 0)
		return (0);
	return (0);
}
