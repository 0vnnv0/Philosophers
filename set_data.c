/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anna <anna@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:01:38 by anschmit          #+#    #+#             */
/*   Updated: 2024/12/17 15:06:21 by anna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutex(t_simulation *simu)
{
	pthread_mutex_init(&simu->running, NULL);
	pthread_mutex_init(&simu->log_mutex, NULL);
}

void	set_mutex_fork(t_simulation *simu)
{
	int	i;

	i = 0;
	while (i < simu->nr_philos)
	{
		simu->philos[i].philo_id = i + 1;
		pthread_mutex_init(&simu->forks[i].mutex, NULL);
		i++;
	}
}

void	set_simulation(t_simulation *simu, int argc, char **argv)
{
	simu->nr_philos = ft_atoi(argv[1]);
	simu->time_to_die = ft_atoi(argv[2]);
	simu->time_to_eat = ft_atoi(argv[3]);
	simu->time_to_sleep = ft_atoi(argv[4]);
	simu->running = 1;
	init_mutex(simu);
	if (argc == 6)
		simu->nr_meals = ft_atoi(argv[5]);
	else
		simu->nr_meals = -1;
	simu->forks = malloc(sizeof(t_fork) * simu->nr_philos);
	if (!simu->forks)
		return ;
	simu->philos = malloc(sizeof(t_philosopher) * simu->nr_philos);
	if (!simu->philos)
		return ;
	set_mutex_fork(simu);
}

void	set_philosophers(t_simulation *simu)
{
	int	i;

	i = 0;
	while (i < simu->nr_philos)
	{
		simu->philos[i].philo_id = i + 1;
		simu->philos[i].meals_eaten = 0;
		simu->philos[i].last_meal_time = ft_get_time();
		simu->philos[i].left_fork = &simu->forks[i];
		if (i == simu->nr_philos - 1)
			simu->philos[i].right_fork = &simu->forks[0];
		else
			simu->philos[i].right_fork = &simu->forks[i + 1];
		simu->philos[i].simu = simu;
		pthread_mutex_init(&simu->philos[i].mutex, NULL);
		i++;
	}
	run_simu(&simu);
}
