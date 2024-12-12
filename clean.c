/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anschmit <anschmit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:09:19 by anschmit          #+#    #+#             */
/*   Updated: 2024/12/12 17:23:48 by anschmit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	clean_philo_mutex(t_simulation *simu, int i)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		pthread_mutex_destroy(&simu->forks[j].mutex);
		j++;
	}
	j = 0;
	while (j < i)
	{
		pthread_mutex_destroy(&simu->philos[j].mutex);
		j++;
	}
	free(simu->forks);
	free(simu->philos);
	return (2);
}

int	clean_mutex(t_simulation *simu)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < simu->nr_philos)
	{
		simu->philos[i].philo_id = i + 1;
		if (pthread_mutex_init(&simu->forks[i].mutex, NULL) != 0)
		{
			while (j < i)
			{
				pthread_mutex_destroy(&simu->forks[j].mutex);
				pthread_mutex_destroy(&simu->philos[j].mutex);
				j++;
			}
			free(simu->forks);
			free(simu->philos);
			return (2);
		}
		if (pthread_mutex_init(&simu->philos[i].mutex, NULL) != 0)
			clean_philo_mutex(simu, i);
		i++;
	}
	return (0);
}
