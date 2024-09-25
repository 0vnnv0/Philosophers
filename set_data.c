/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anna <anna@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:23:40 by anna              #+#    #+#             */
/*   Updated: 2024/09/25 17:47:39 by anna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_set_simu(t_simulation *simu, int argc, char **argv)
{
	int	i;

	i = 0;
	simu->nr_of_philosophers = ft_atoi(argv[1]);
	simu->time_to_die = ft_atoi(argv[2]);
	simu->time_to_eat = ft_atoi(argv[3]);
	simu->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		simu->nr_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		simu->nr_of_times_each_philosopher_must_eat = 0;
	simu->philos = malloc(sizeof(t_philosopher) * simu->nr_of_philosophers);
	if (!simu->philos)
		return ;
	simu->forks = malloc(sizeof(t_fork) * simu->nr_of_philosophers);
	if (!simu->forks)
		return ;
	while (i < simu->nr_of_philosophers)
	{
		simu->forks[i].fork_id = i;	
		simu->philos[i].philo_id = i + 1;
		printf("%d\n", simu->philos[i].philo_id);
		i++;
	}
}

void	ft_set_philos(t_simulation *simu)
{
	int	i;

	i = 0;
	while (i < simu->nr_of_philosophers)
	{
		simu->philos[i].last_meal_time = gettimeofday();
		simu->philos[i].meals_eaten = 0;
	}
}
