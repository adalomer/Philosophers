/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 00:03:23 by omadali           #+#    #+#             */
/*   Updated: 2025/05/10 18:35:03 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_philo_death(t_data *data, int i)
{
	long long	last_meal;

	pthread_mutex_lock(&data->philos[i].meal_mutex);
	last_meal = data->philos[i].last_meal_time;
	pthread_mutex_unlock(&data->philos[i].meal_mutex);
	if ((get_time() - last_meal) >= data->time_to_die)
	{
		pthread_mutex_lock(&data->write_mutex);
		printf("%lld %d died\n", get_time() - data->start_time, data->philos[i].id + 1);
		pthread_mutex_lock(&data->sim_mutex);
		data->sim_over = 1;
		pthread_mutex_unlock(&data->sim_mutex);
		pthread_mutex_unlock(&data->write_mutex);
		return (1);
	}
	return (0);
}

static int	check_all_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (check_philo_death(data, i))
			return (1);
		i++;
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_all_philos(data))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
