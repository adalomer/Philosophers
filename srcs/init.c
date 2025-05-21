/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 00:02:55 by omadali           #+#    #+#             */
/*   Updated: 2025/03/13 00:03:02 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_data(t_data *data, char **argv)
{
	int	i;

	data->num_philos = ft_atoi(argv[1]);
	if (data->num_philos <= 0)
		return (printf("Error: Number of philosophers must be positive\n"), 1);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->meals_required = (argv[5]) ? ft_atoi(argv[5]) : -1;
	data->sim_over = 0;
	data->start_time = get_time();
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->forks || !data->philos)
		return (printf("Error: Memory allocation failed\n"), 1);
	pthread_mutex_init(&data->write_mutex, NULL);
	pthread_mutex_init(&data->sim_mutex, NULL);
	pthread_mutex_init(&data->start_mutex, NULL);
	pthread_mutex_lock(&data->start_mutex);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&data->philos[i].meal_mutex, NULL);
		data->philos[i].id = i;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].data = data;
		i++;
	}
	return (0);
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->sim_mutex);
	pthread_mutex_destroy(&data->start_mutex);
	free(data->forks);
	free(data->philos);
}
