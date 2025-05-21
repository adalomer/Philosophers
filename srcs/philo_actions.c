/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 00:03:10 by omadali           #+#    #+#             */
/*   Updated: 2025/03/13 00:03:13 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	take_forks(t_philo *philo, t_data *data)
{
	if (data->num_philos == 1)
	{
		pthread_mutex_lock(&data->forks[0]);
		return;
	}
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&data->forks[philo->id]);
		usleep(100);
		pthread_mutex_lock(&data->forks[(philo->id + 1) % data->num_philos]);
	}
	else
	{
		usleep(100);
		pthread_mutex_lock(&data->forks[(philo->id + 1) % data->num_philos]);
		pthread_mutex_lock(&data->forks[philo->id]);
	}
}

static void	release_forks(t_philo *philo, t_data *data)
{
	if (data->num_philos == 1)
	{
		pthread_mutex_unlock(&data->forks[0]);
		return;
	}
	pthread_mutex_unlock(&data->forks[philo->id]);
	pthread_mutex_unlock(&data->forks[(philo->id + 1) % data->num_philos]);
}

static int	print_status(t_data *data, int philo_id, char *status)
{
	pthread_mutex_lock(&data->sim_mutex);
	if (!data->sim_over)
	{
		pthread_mutex_unlock(&data->sim_mutex);
		pthread_mutex_lock(&data->write_mutex);
		printf("%lld %d %s\n", get_time() - data->start_time, philo_id + 1, status);
		pthread_mutex_unlock(&data->write_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->sim_mutex);
	return (0);
}

static void	eat(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	if (!print_status(data, philo->id, "is eating"))
	{
		release_forks(philo, data);
		return ;
	}
	ft_usleep(data->time_to_eat);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	release_forks(philo, data);
}

void	*philosopher_routine(void *arg)
{
	t_philo		*philo;
	t_data		*data;

	philo = (t_philo *)arg;
	data = philo->data;
	pthread_mutex_lock(&data->start_mutex);
	pthread_mutex_unlock(&data->start_mutex);
	while (1)
	{
		pthread_mutex_lock(&data->sim_mutex);
		if (data->sim_over)
		{
			pthread_mutex_unlock(&data->sim_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->sim_mutex);
		take_forks(philo, data);
		if (!print_status(data, philo->id, "has taken a fork"))
		{
			release_forks(philo, data);
			break ;
		}
		if (data->num_philos == 1)
		{
			ft_usleep(data->time_to_die);
			pthread_mutex_lock(&data->sim_mutex);
			data->sim_over = 1;
			pthread_mutex_unlock(&data->sim_mutex);
			release_forks(philo, data);
			break;
		}
		eat(philo, data);
		if (!print_status(data, philo->id, "is sleeping"))
			break ;
		ft_usleep(data->time_to_sleep);
		if (!print_status(data, philo->id, "is thinking"))
			break ;
	}
	return (NULL);
} 