/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 00:03:23 by omadali           #+#    #+#             */
/*   Updated: 2025/05/22 04:54:59 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	print_death_message(t_data *data, int philo_id)
{
	pthread_mutex_lock(&data->write_mutex);
	printf("%lld %d died\n", get_time() - data->start_time, philo_id + 1);
	pthread_mutex_lock(&data->sim_mutex);
	data->sim_over = 1;
	pthread_mutex_unlock(&data->sim_mutex);
	pthread_mutex_unlock(&data->write_mutex);
}

static int	check_philo_death(t_data *data, int i)
{
	long long	last_meal;

	pthread_mutex_lock(&data->philos[i].meal_mutex);
	last_meal = data->philos[i].last_meal_time;
	pthread_mutex_unlock(&data->philos[i].meal_mutex);
	if ((get_time() - last_meal) >= data->time_to_die)
	{
		print_death_message(data, data->philos[i].id);
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

static int	check_meals_required(t_data *data)
{
	int	i;

	if (data->meals_required == -1)
		return (0);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].meal_mutex);
		if (data->philos[i].meals_eaten < data->meals_required)
		{
			pthread_mutex_unlock(&data->philos[i].meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		i++;
	}
	return (1);
}

static void	end_simulation(t_data *data)
{
	pthread_mutex_lock(&data->sim_mutex);
	data->sim_over = 1;
	pthread_mutex_unlock(&data->sim_mutex);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	pthread_mutex_lock(&data->start_mutex);
	data->start = 1;
	pthread_mutex_unlock(&data->start_mutex);
	while (1)
	{
		if (check_all_philos(data))
			return (NULL);
		if (check_meals_required(data))
		{
			end_simulation(data);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
