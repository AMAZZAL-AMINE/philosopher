/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazzal <mamazzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:54:10 by mamazzal          #+#    #+#             */
/*   Updated: 2023/06/01 14:27:57 by mamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <stdbool.h>

typedef struct s_data
{
	int				is_dead;
	int				n_philos;
	int				n_time_die;
	int				n_time_sleep;
	int				n_time_eat;
	int				n_must_eat;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*mutex;
}	t_shared_source;

typedef struct t_philo
{
	int				p_id;
	pthread_t		philo;
	int				left_mutex;
	int				right_mutex;
	long long		created_at;
	long long		last_eat;
	int				is_dead;
	int				meals;
	int				ichb3a;
	t_shared_source	*data;
}	t_philo;

long long	ft_atoi(const char *str);
long		long	get_current_time(void);
void		sleep_time(int time, t_philo *philo);
void		print_action(char *msg, t_philo *philo);
void		print_eat(t_philo *philo);
int			philo_todo(t_philo *philo);
void		*philo_routine(void *data);
void		print_died(char *msg, t_philo *philo);
int			check_is_die(t_philo *philo);
int			niga_tive(long long n);
int			is_not_numbers(char **argv);
int			is_error(int argc, char **argv);
int			join_and_destroy(t_philo *philo);
int			init_shared_data(t_philo *philo, int argc, char **argv);
int			init_mutexs(t_philo *philo);
int			init_threads(t_philo *philo);
void		free_allocation(t_philo *philo, t_shared_source *source);
int			print_error(char *str);
int			start_dinner(char **argv, t_philo *philo, int argc);
#endif