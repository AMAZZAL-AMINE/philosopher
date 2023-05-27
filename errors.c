/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazzal <mamazzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:38:53 by mamazzal          #+#    #+#             */
/*   Updated: 2023/05/27 19:00:41 by mamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int niga_tive(int n) {
    if (n <= 0)
        return 0;
    return 1;
}


int is_not_numbers(char **argv) {
    int count = 0;
    int index;
    while (argv[count]) {
      index = 0;
      while (argv[count][index]) {
        if (argv[count][index] < '0' || argv[count][index] > '9') {
          return 1;
        }
        index++;
      }
      count++;
    }
    return 0;
}