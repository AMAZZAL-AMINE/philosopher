/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazzal <mamazzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:03:22 by mamazzal          #+#    #+#             */
/*   Updated: 2023/05/31 15:31:43 by mamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	main_functions(t_philo *philo, t_shared_source *source)
{
	if (join_and_destroy(philo) == 1)
	{
		printf("Error: join or destroy\n");
		free_allocation(philo, source);
		return (1);
	}
	free_allocation(philo, source);
	return (0);
}

int	init_data_philo(char **av, t_philo *philo, t_shared_source *src)
{
	int	count;
	int	n_philo;

	n_philo = ft_atoi(av[1]);
	count = 0;
	while (count < n_philo)
	{
		philo[count].data = src;
		count++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_shared_source	*source;
	int				count;
	t_philo			*philo;

	if (is_error(argc, argv) == 1 || (argc > 6 && argc < 5))
		return (1);
	count = 0;
	philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	source = malloc(sizeof(t_shared_source));
	if (!philo || !source)
		return (1);
	init_data_philo(argv, philo, source);
	if (start_dinner(argv, philo, argc))
	{
		free_allocation(philo, source);
		return (1);
	}
	while (1)
		if (check_is_die(philo) || check_ichb3a(philo))
			break ;
	if (main_functions(philo, source))
		return (1);
	return (0);
}
