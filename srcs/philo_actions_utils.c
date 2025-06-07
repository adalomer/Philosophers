/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 00:03:10 by omadali           #+#    #+#             */
/*   Updated: 2025/06/03 22:10:06 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	take_forks(t_philo *philo, t_data *data)
{
	if (data->num_philos == 1)
	{
		pthread_mutex_lock(&data->forks[0]);
		return ;
	}
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&data->forks[philo->id]);
		pthread_mutex_lock(&data->forks[(philo->id + 1) % data->num_philos]);
	}
	else
	{
		pthread_mutex_lock(&data->forks[(philo->id + 1) % data->num_philos]);
		pthread_mutex_lock(&data->forks[philo->id]);
	}
}

void	release_forks(t_philo *philo, t_data *data)
{
	if (data->num_philos == 1)
	{
		pthread_mutex_unlock(&data->forks[0]);
		return ;
	}
	pthread_mutex_unlock(&data->forks[philo->id]);
	pthread_mutex_unlock(&data->forks[(philo->id + 1) % data->num_philos]);
}

int	print_status(t_data *data, int philo_id, char *status)
{
	long long	current_time;

	pthread_mutex_lock(&data->sim_mutex);
	if (!data->sim_over)
	{
		pthread_mutex_unlock(&data->sim_mutex);
		pthread_mutex_lock(&data->write_mutex);
		current_time = get_time() - data->start_time;
		printf("%lld %d %s\n", current_time, philo_id + 1, status);
		pthread_mutex_unlock(&data->write_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->sim_mutex);
	return (0);
}

void	update_meal_info(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
}
