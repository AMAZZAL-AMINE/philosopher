/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazzal <mamazzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:31:25 by mamazzal          #+#    #+#             */
/*   Updated: 2023/06/01 14:27:15 by mamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	niga_tive(long long n)
{
	if (n <= 0)
		return (0);
	return (1);
}

int	is_not_numbers(char **argv)
{
	int	count;
	int	index;

	count = 0;
	while (argv[count])
	{
		index = 0;
		while (argv[count][index])
		{
			if ((argv[count][index] < '0' || argv[count][index] > '9') && \
			(argv[count][index] != '-' && argv[count][index] != '+'))
				return (1);
			index++;
		}
		count++;
	}
	return (0);
}

int	is_error(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (print_error("Error: Wrong number of arguments\n"));
	if (is_not_numbers(argv + 1))
		return (print_error("Error: arguments must be numbers\n"));
	if (ft_atoi(argv[1]) > 2147483647 || \
		ft_atoi(argv[2]) > 2147483647 || ft_atoi(argv[3]) > 2147483647 || \
		ft_atoi(argv[4]) > 2147483647)
		return (print_error("Error: Range Too big\n"));
	if (argc == 6 && ft_atoi(argv[5]) > 2147483647)
		return (print_error("Error: Range Too big\n"));
	if (!niga_tive(ft_atoi(argv[1])) || !niga_tive(ft_atoi(argv[2])))
		return (print_error("Error: arguments must be positive numbers\n"));
	return (0);
}
