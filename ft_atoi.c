/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazzal <mamazzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:13:00 by mamazzal          #+#    #+#             */
/*   Updated: 2023/06/01 14:27:36 by mamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_atoi(const char *str)
{
	int			ci;
	long long	fr;
	int			isminus;

	ci = 0;
	isminus = 1;
	fr = 0;
	while ((str[ci] >= '\t' && str[ci] <= '\r') || str[ci] == ' ')
	{
		ci++;
	}
	if (str[ci] == '-' || str[ci] == '+')
	{
		if (str[ci] == '-')
		{
			isminus = -1;
		}
		ci++;
	}
	while (str[ci] >= '0' && str[ci] <= '9')
	{
		fr = (fr * 10) + (str[ci] - '0');
		ci++;
	}
	return (fr * isminus);
}
