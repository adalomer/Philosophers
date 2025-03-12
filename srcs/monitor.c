/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 00:03:23 by omadali           #+#    #+#             */
/*   Updated: 2025/03/13 00:03:25 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*monitor_routine(void *arg)
{
	t_data		*data;
	int			i;

	data = (t_data *)arg;
	while (!data->sim_over)
	{
		i = 0;
		while (i < data->num_philos)
		{
			if ((get_time() - data->philos[i].last_meal_time) > data->time_to_die)
			{
				pthread_mutex_lock(&data->write_mutex);
				printf("%lld %d died\n", get_time() - data->start_time, data->philos[i].id + 1);
				data->sim_over = 1;
				pthread_mutex_unlock(&data->write_mutex);
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
