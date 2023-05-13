/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazzal <mamazzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:54:10 by mamazzal          #+#    #+#             */
/*   Updated: 2023/05/13 23:47:55 by mamazzal         ###   ########.fr       */
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

typedef struct s_philo
{
    int n_philos;
    int n_time_die;
    int n_time_sleep;
    int n_time_eat;
    int p_id;
    pthread_t *philos;
    pthread_mutex_t *forks;
    struct timeval *tv_cretaed_at;
    struct timezone *tz_cretaed_at;
    struct timeval *tv_last_eat;
    int is_dead;
} s_philo;



int ft_atoi(const char *str);
void error_msg(char *msg);
long long get_current_time();
long long get_time_millsec();
void greate_sleep(int time);
void print_eat(struct timeval tv, int t_id, s_philo *p_data);
void printf_actions(char *msg, struct timeval tv, int t_id) ;
long long time_to_millscnd(struct timeval tv);

#endif