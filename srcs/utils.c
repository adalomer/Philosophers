/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 03:00:00 by omadali           #+#    #+#             */
/*   Updated: 2025/03/13 00:02:44 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(int milliseconds)
{
	long long	start_time;
	long long	current_time;

	start_time = get_time();
	while (1)
	{
		current_time = get_time();
		if ((current_time - start_time) >= milliseconds)
			break;
		usleep(10);
	}
}

static int	ft_isspace(int c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static long	ft_atol(const char *str)
{
	int		i;
	int		sign;
	long result;

	i = 0;
	sign = 1;
	result = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	ft_atoi(const char *str)
{
	return ((int)ft_atol(str));
}
