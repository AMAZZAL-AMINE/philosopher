/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazzal <mamazzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:54:10 by mamazzal          #+#    #+#             */
/*   Updated: 2023/05/16 17:36:10 by mamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>


typedef struct s_data
{
    int n_philos;
    int n_time_die;
    int n_time_sleep;
    int n_time_eat;
    long long start_time;
    pthread_mutex_t exit_lock;
    pthread_mutex_t print_lock;
} s_shared_source;

typedef struct s_philo
{
    int p_id;
    pthread_t philo;
    pthread_mutex_t mutex;
    pthread_mutex_t left_mutex;
    long long created_at;
    long long last_eat;
    int is_dead;
    s_shared_source *data;
} s_philo;

int ft_atoi(const char *str);

#endif