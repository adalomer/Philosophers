/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 00:03:10 by omadali           #+#    #+#             */
/*   Updated: 2025/06/11 20:12:58 by omadali          ###   ########.fr       */
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
		usleep(1);
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

int	check_simulation_status(t_data *data)
{
	int	status;

	pthread_mutex_lock(&data->sim_mutex);
	status = data->sim_over;
	pthread_mutex_unlock(&data->sim_mutex);
	return (status);
}

void	handle_single_philosopher(t_philo *philo, t_data *data)
{
	ft_usleep(data->time_to_die);
	pthread_mutex_lock(&data->sim_mutex);
	data->sim_over = 1;
	pthread_mutex_unlock(&data->sim_mutex);
	release_forks(philo, data);
}
