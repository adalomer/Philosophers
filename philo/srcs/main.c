/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 02:59:22 by omadali           #+#    #+#             */
/*   Updated: 2025/06/12 18:31:45 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static int	create_threads(t_data *data)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				philosopher_routine, &data->philos[i]))
			return (1);
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, data))
		return (1);
	pthread_mutex_unlock(&data->start_mutex);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL))
			return (1);
		i++;
	}
	if (pthread_join(monitor, NULL))
		return (1);
	return (0);
}

void	ft_thinktime(t_data *data)
{
	int	thinktime;

	thinktime = (data->time_to_die - data->time_to_eat
			- data->time_to_sleep) / 2;
	if (thinktime > 0)
		ft_usleep(thinktime);
}

static int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo num_philos time_to_die time_to_eat ");
		printf("time_to_sleep [meals_required]\n");
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("Error: Arguments must be positive numbers\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	cleanup(t_data *data)
{
	destroy_philo_mutexes(data);
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->sim_mutex);
	pthread_mutex_destroy(&data->start_mutex);
	free(data->forks);
	free(data->philos);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv))
		return (1);
	if (init_data(&data, argv))
		return (1);
	if (create_threads(&data))
		return (1);
	cleanup(&data);
	return (0);
}
