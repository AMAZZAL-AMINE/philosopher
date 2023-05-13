/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazzal <mamazzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:03:22 by mamazzal          #+#    #+#             */
/*   Updated: 2023/05/13 22:36:39 by mamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_value_struct(char **argv, s_philo *p_data) {
	int count = 0;
	while (count < ft_atoi(argv[1])) {
		p_data[count].n_philos = ft_atoi(argv[1]);
		p_data[count].n_time_die = ft_atoi(argv[2]);
		p_data[count].n_time_eat = ft_atoi(argv[3]);
		p_data[count].n_time_sleep = ft_atoi(argv[4]);
		p_data[count].philos = malloc(sizeof(pthread_t) * p_data->n_philos);
		p_data[count].tv_last_eat = malloc(sizeof(struct timeval) * p_data->n_philos);
		p_data[count].forks = malloc(sizeof(pthread_mutex_t) * p_data->n_philos);
		p_data[count].tv_cretaed_at = malloc(sizeof(struct timeval) * p_data->n_philos);
		count++;
	}
}

void *philo_routin(void *input) {
    s_philo *p_data = (s_philo *)input;
	pthread_mutex_t right_fork = p_data->forks[p_data->p_id];
	pthread_mutex_t left_fork =  p_data->forks[(p_data->p_id + 1) % p_data->n_philos];
	while (1) {
		printf_actions("is thinking", *p_data->tv_cretaed_at, p_data->p_id);
		pthread_mutex_lock(&right_fork);
		printf_actions("has taken a fork", *p_data->tv_cretaed_at, p_data->p_id);
		pthread_mutex_lock(&left_fork);
		printf_actions("has taken a fork", *p_data->tv_cretaed_at, p_data->p_id);
		print_eat(*p_data->tv_cretaed_at, p_data->p_id, p_data);
		greate_sleep(p_data->n_time_eat);
		pthread_mutex_unlock(&left_fork);
		printf_actions("is sleeping", *p_data->tv_cretaed_at, p_data->p_id);
		greate_sleep(p_data->n_time_sleep);
		pthread_mutex_unlock(&right_fork);
		pthread_mutex_lock(&right_fork);
		if ((get_current_time() - time_to_millscnd(*p_data->tv_last_eat)) >= p_data->n_time_die) {
			printf_actions("died", *p_data->tv_cretaed_at, p_data->p_id);
			exit(1);
		}
		pthread_mutex_unlock(&right_fork);
	}
    return NULL;
}

int	p_create_threads(s_philo *p_data) {
	int	count = 0;
	while (count < p_data->n_philos) {
		p_data[count].p_id = count + 1;
		gettimeofday(p_data[count].tv_cretaed_at, p_data[count].tz_cretaed_at);
		if (pthread_create(&p_data[count].philos[count], NULL, philo_routin, &p_data[count]) != 0)
			error_msg("Error create thread");
		count++;
	}
	count = 0;
	while (count < p_data->n_philos) {
		pthread_join(p_data->philos[count], NULL);
		count++;
	}
	return 0;
}

int	create_reight_forks(s_philo *p_data) {
	int count = 0;
	while (count < p_data[0].n_philos) {
		if (pthread_mutex_init(&p_data[count].forks[count], NULL)) {
			error_msg("Error creating  Mutex");
		}
		count++;
	}
	return 0;
}

void time_to_dinner(char **argv, s_philo *p_data) {
	set_value_struct(argv, p_data);
	create_reight_forks(p_data);
	p_create_threads(p_data);
}

int main(int argc, char **argv) {
	if (argc != 5) {
		error_msg("Error : Argments");
	}
	s_philo *p_data = malloc(sizeof(s_philo) * ft_atoi(argv[1])); 
	time_to_dinner(argv, p_data);
	free(p_data);
	return 0;
}
