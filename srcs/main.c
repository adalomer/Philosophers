/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 02:59:22 by omadali           #+#    #+#             */
/*   Updated: 2025/03/13 00:04:58 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor;
	int			i;

	if (argc < 5 || argc > 6)
		return (printf("Usage: ./philo num_philos time_to_die time_to_eat time_to_sleep [meals_required]\n"), 1);
	if (init_data(&data, argv))
		return (1);
	i = 0;
	while (i < data.num_philos)
	{
		pthread_create(&data.philos[i].thread, NULL, philosopher_routine, &data.philos[i]);
		i++;
	}
	pthread_create(&monitor, NULL, monitor_routine, &data);
	i = 0;
	while (i < data.num_philos)
	{
		pthread_join(data.philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	cleanup(&data);
	return (0);
}
