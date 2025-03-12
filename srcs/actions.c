/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 00:03:10 by omadali           #+#    #+#             */
/*   Updated: 2025/03/13 00:03:13 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*philosopher_routine(void *arg)
{
	t_philo		*philo;
	t_data		*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (!data->sim_over)
	{
		pthread_mutex_lock(&data->forks[philo->id]);
		pthread_mutex_lock(&data->write_mutex);
		printf("%lld %d has taken a fork\n", get_time() - data->start_time, philo->id + 1);
		pthread_mutex_unlock(&data->write_mutex);

		pthread_mutex_lock(&data->forks[(philo->id + 1) % data->num_philos]);
		pthread_mutex_lock(&data->write_mutex);
		printf("%lld %d is eating\n", get_time() - data->start_time, philo->id + 1);
		pthread_mutex_unlock(&data->write_mutex);

		philo->last_meal_time = get_time();
		ft_usleep(data->time_to_eat);
		philo->meals_eaten++;

		pthread_mutex_unlock(&data->forks[philo->id]);
		pthread_mutex_unlock(&data->forks[(philo->id + 1) % data->num_philos]);

		pthread_mutex_lock(&data->write_mutex);
		printf("%lld %d is sleeping\n", get_time() - data->start_time, philo->id + 1);
		pthread_mutex_unlock(&data->write_mutex);
		ft_usleep(data->time_to_sleep);

		pthread_mutex_lock(&data->write_mutex);
		printf("%lld %d is thinking\n", get_time() - data->start_time, philo->id + 1);
		pthread_mutex_unlock(&data->write_mutex);
	}
	return (NULL);
}
