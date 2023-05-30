/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazzal <mamazzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:31:25 by mamazzal          #+#    #+#             */
/*   Updated: 2023/05/30 14:01:10 by mamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int is_error(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: wrong number of arguments\n");
		return 1;
	}

	if (is_not_numbers(argv + 1))
	{
		printf("Error: arguments must be numbers\n");
		return 1;
	}

	if (!niga_tive(ft_atoi(argv[1])) || !niga_tive(ft_atoi(argv[2])))
	{
		printf("Error: arguments must be positive numbers\n");
		return 1;
	}
	return 0;
}
