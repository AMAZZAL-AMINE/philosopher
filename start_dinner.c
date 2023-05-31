/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazzal <mamazzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:20:31 by mamazzal          #+#    #+#             */
/*   Updated: 2023/05/31 15:40:00 by mamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_dinner(char **argv, t_philo *philo, int argc)
{
	if (init_shared_data(philo, argc, argv))
		return (print_error("Error:  Shared Data\n"));
	if (init_mutexs(philo))
		return (print_error("Error:  Mutexs\n"));
	if (init_threads(philo))
		return (print_error("Error:  Threads\n"));
	return (0);
}
