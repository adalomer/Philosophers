/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 00:03:10 by omadali           #+#    #+#             */
/*   Updated: 2025/06/03 21:28:07 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_simulation_status(t_data *data)
{
	int	status;

	pthread_mutex_lock(&data->sim_mutex);
	status = data->sim_over;
	pthread_mutex_unlock(&data->sim_mutex);
	return (status);
}

static void	release_forks(t_philo *philo, t_data *data)
{
	if (data->num_philos == 1)
	{
		pthread_mutex_unlock(&data->forks[0]);
		return ;
	}
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&data->forks[philo->id]);
		pthread_mutex_unlock(&data->forks[(philo->id + 1) % data->num_philos]);
	}
	else
	{
		pthread_mutex_unlock(&data->forks[(philo->id + 1) % data->num_philos]);
		pthread_mutex_unlock(&data->forks[philo->id]);
	}
}

static int	print_status(t_data *data, int philo_id, char *status)
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

static void	handle_single_philosopher(t_philo *philo, t_data *data)
{
	ft_usleep(data->time_to_die);
	pthread_mutex_lock(&data->sim_mutex);
	data->sim_over = 1;
	pthread_mutex_unlock(&data->sim_mutex);
	release_forks(philo, data);
}

static void	philosopher_cycle(t_philo *philo, t_data *data)
{
	int thinktime;
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
	if (check_simulation_status(data))
		return ;
	if (!print_status(data, philo->id, "is sleeping"))
		return ;
	ft_usleep(data->time_to_sleep);
	if (check_simulation_status(data))
		return ;
	if (!print_status(data, philo->id, "is thinking"))
		return ;
	thinktime = data->time_to_die - data->time_to_eat - data->time_to_sleep;
	if (thinktime > 0)
		ft_usleep(thinktime / 2);
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
