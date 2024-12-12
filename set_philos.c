/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_philos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anschmit <anschmit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:01:38 by anschmit          #+#    #+#             */
/*   Updated: 2024/12/12 18:00:34 by anschmit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_create_threads(t_simulation *simu)
{
	int	i;

	i = 0;
	while (i < simu->nr_philos)
	{
		if (pthread_create(&simu->philos[i].thread, NULL, \
		ft_philo_routine, &simu->philos[i]) != 0)
		{
			printf("Failed to create thread for \
			 philosopher %d\n", i + 1);
			exit(1);
		}
		i++;
	}
}

void	ft_join_threads(t_simulation *simu)
{
	int	i;
	
	i = 0;
	while (i < simu->nr_philos)
	{
		if (pthread_join(simu->philos[i].thread, NULL) != 0)
		{
			printf("Failed to join thread for \
			philosopher %d\n", i + 1);
			exit (1);
		}
		i++;
	}
}


long long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * (long long)1000LL) + (tv.tv_usec / 1000);
}

void	set_philosophers(t_simulation *simu)
{
	int	i;

	i = 0;
	while (i < simu->nr_philos)
	{
		simu->philos[i].philo_id = i;
		simu->philos[i].meals_eaten = 0;
		simu->philos[i].last_meal_time = ft_get_time();
		simu->philos[i].left_fork = &simu->forks[i];
		if (i == simu->nr_philos - 1)
			simu->philos[i].right_fork = &simu->forks[0];
		else
			simu->philos[i].right_fork = &simu->forks[i + 1];
		simu->philos[i].simu = simu;
		i++;
	}
}
