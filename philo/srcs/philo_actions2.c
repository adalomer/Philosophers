/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 21:14:52 by omadali           #+#    #+#             */
/*   Updated: 2025/06/12 18:30:00 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_cycle2(t_philo *philo, t_data *data)
{
	if (check_simulation_status(data))
		return ;
	if (!print_status(data, philo->id, "is sleeping"))
		return ;
	ft_usleep(data->time_to_sleep);
	if (check_simulation_status(data))
		return ;
	if (!print_status(data, philo->id, "is thinking"))
		return ;
}

void	ft_whileloop(t_data *data, t_philo *philo)
{
	while (1)
	{
		if (check_simulation_status(data))
			break ;
		if (philosopher_cycle(philo, data))
			break ;
		if (check_simulation_status(data))
			break ;
	}
}
