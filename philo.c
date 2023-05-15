/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazzal <mamazzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:03:22 by mamazzal          #+#    #+#             */
/*   Updated: 2023/05/15 17:57:41 by mamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_value_struct(char **argv, s_philo *p_data) {
	p_data->data->n_philos = ft_atoi(argv[1]);
	p_data->data->n_time_die = ft_atoi(argv[2]);
	p_data->data->n_time_eat = ft_atoi(argv[3]);
	p_data->data->n_time_sleep = ft_atoi(argv[4]);
	struct timeval start;
	gettimeofday(&start, NULL);
	p_data->data->start_time = (start.tv_sec * 1000LL) + (start.tv_usec / 1000);
	pthread_mutex_init(&p_data->data->exit_lock, NULL);
	pthread_mutex_init(&p_data->data->print_lock, NULL);
}

void *philo_routin(void *input) {
    s_philo *p_data = (s_philo *)input;
	while (1) {
		pthread_mutex_t left_fork = p_data[(p_data->p_id + 1) % p_data->data->n_philos].fork;
		//print
		pthread_mutex_lock(&p_data->data->print_lock);
		printf_actions("is thinking", p_data);
		pthread_mutex_unlock(&p_data->data->print_lock);

		//take right fork
		pthread_mutex_lock(&p_data->fork);
		//print
		pthread_mutex_lock(&p_data->data->print_lock);
		printf_actions("has taken a fork", p_data);
		pthread_mutex_unlock(&p_data->data->print_lock);
		//take left fork
		pthread_mutex_lock(&left_fork);
		//print
		pthread_mutex_lock(&p_data->data->print_lock);
		printf_actions("has taken a fork",  p_data);
		pthread_mutex_unlock(&p_data->data->print_lock);
		//print
		pthread_mutex_lock(&p_data->data->print_lock);
		print_eat(p_data->p_id, p_data);
		pthread_mutex_unlock(&p_data->data->print_lock);
		//sleep
		greate_sleep(p_data->data->n_time_eat, p_data);
		//put both forks
		pthread_mutex_unlock(&left_fork);
		pthread_mutex_unlock(&p_data->fork);
		//print
		pthread_mutex_lock(&p_data->data->print_lock);
		printf_actions("is sleeping", p_data);
		greate_sleep(p_data->data->n_time_sleep, p_data);
		pthread_mutex_unlock(&p_data->data->print_lock);
		return NULL;
	}
	return NULL;
}

int	p_create_threads(s_philo *p_data) {
	int count = 0;
	while (count < p_data->data->n_philos) {
		p_data[count].p_id = count + 1;
		p_data[count].created_at = get_current_time();
		pthread_create(&p_data[count].philo, NULL, philo_routin, &p_data[count]);
		count++;
	}
	count = 0;
	while (count < p_data->data->n_philos) {
		pthread_join(p_data[count].philo, NULL);
		count++;
	}
	return 0;
}

int	create_mutex(s_philo *p_data) {
	int count = 0;
	while (count < p_data->data->n_philos) {
		pthread_mutex_init(&p_data[count].fork, NULL);
		count++;
	}
	return 0;
}


void time_to_dinner(char **argv, s_philo *p_data) {
	set_value_struct(argv, p_data);
	create_mutex(p_data);
	p_create_threads(p_data);
}

int main(int argc, char **argv) {
	(void)argc;
	s_philo *p_philo = malloc(sizeof(s_philo) * ft_atoi(argv[1]));
	s_data *p_data = malloc(sizeof(s_data));
	int count = 0;
	while (count < ft_atoi(argv[1])) {
		p_philo[count].data = p_data;
		count++;
	}
	time_to_dinner(argv, p_philo);
}
