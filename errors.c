/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazzal <mamazzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:38:53 by mamazzal          #+#    #+#             */
/*   Updated: 2023/05/30 16:25:46 by mamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	niga_tive(int n)
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
			if (argv[count][index] < '0' || argv[count][index] > '9')
				return (1);
			index++;
		}
		count++;
	}
	return (0);
}
