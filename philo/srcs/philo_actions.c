/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 00:03:10 by omadali           #+#    #+#             */
/*   Updated: 2025/06/11 21:19:34 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	print_status(t_data *data, int philo_id, char *status)
{
	pthread_mutex_lock(&data->sim_mutex);
	if (data->sim_over)
	{
		pthread_mutex_unlock(&data->sim_mutex);
		return (0);
	}
	pthread_mutex_unlock(&data->sim_mutex);
	pthread_mutex_lock(&data->write_mutex);
	printf("%lld %d %s\n", get_time() - data->start_time,
		philo_id + 1, status);
	pthread_mutex_unlock(&data->write_mutex);
	return (1);
}

static void	update_meal_info(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
}

static void	eat(t_philo *philo, t_data *data)
{
	update_meal_info(philo);
	if (!print_status(data, philo->id, "is eating"))
	{
		release_forks(philo, data);
		return ;
	}
	ft_usleep(data->time_to_eat);
	release_forks(philo, data);
}

void	philosopher_cycle(t_philo *philo, t_data *data)
{
	if (check_simulation_status(data))
		return ;
	take_forks(philo, data);
	if (check_simulation_status(data))
	{
		release_forks(philo, data);
		return ;
	}
	if (!print_status(data, philo->id, "has taken a fork"))
	{
		release_forks(philo, data);
		return ;
	}
	if (data->num_philos == 1)
	{
		handle_single_philosopher(philo, data);
		return ;
	}
	eat(philo, data);
	philo_cycle2(philo, data);
	ft_thinktime(data);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		if (&data->start)
			break ;
	}
	while (1)
	{
		if (check_simulation_status(data))
			break ;
		philosopher_cycle(philo, data);
		if (check_simulation_status(data))
			break ;
	}
	return (NULL);
}
