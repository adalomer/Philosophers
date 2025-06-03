/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 02:58:10 by omadali           #+#    #+#             */
/*   Updated: 2025/06/03 22:07:46 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	meal_mutex;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	int				sim_over;
	int				start;
	long long		start_time;
	pthread_mutex_t	sim_mutex;
	pthread_mutex_t	start_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;
	t_philo			*philos;
}	t_data;

/* utils.c */
long long	get_time(void);
void		ft_usleep(int milliseconds);
int			ft_atoi(const char *str);

/* init.c */
int			init_data(t_data *data, char **argv);
void		cleanup(t_data *data);

/* actions.c */
void		*philosopher_routine(void *arg);
void	take_forks(t_philo *philo, t_data *data);
int	check_simulation_status(t_data *data);
void	release_forks(t_philo *philo, t_data *data);

/* monitor.c */
void		*monitor_routine(void *arg);

#endif
