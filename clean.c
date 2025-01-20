/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anna <anna@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:09:19 by anschmit          #+#    #+#             */
/*   Updated: 2024/12/31 19:48:46 by anna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	clean_philo_mutex(t_data *dinner, int i)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		pthread_mutex_destroy(&dinner->forks[j].mutex);
		j++;
	}
	j = 0;
	while (j < i)
	{
		pthread_mutex_destroy(&dinner->philos[j].mutex);
		j++;
	}
	free(dinner->forks);
	free(dinner->philos);
	return (2);
}

int	clean_mutex(t_data *dinner)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < dinner->nr_philos)
	{
		dinner->philos[i].philo_id = i + 1;
		if (pthread_mutex_init(&dinner->forks[i].mutex, NULL) != 0)
		{
			while (j < i)
			{
				pthread_mutex_destroy(&dinner->forks[j].mutex);
				pthread_mutex_destroy(&dinner->philos[j].mutex);
				j++;
			}
			free(dinner->forks);
			free(dinner->philos);
			return (2);
		}
		if (pthread_mutex_init(&dinner->philos[i].mutex, NULL) != 0)
			clean_philo_mutex(dinner, i);
		i++;
	}
	return (0);
}
