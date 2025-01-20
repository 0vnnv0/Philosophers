/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anschmit <anschmit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:52:24 by anschmit          #+#    #+#             */
/*   Updated: 2025/01/15 18:46:24 by anschmit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_dinner(t_data *dinner)
{
	int	i;

	while (1)
	{
		pthread_mutex_lock(&dinner->run_mutex);
		if (!dinner->running)
		{
			pthread_mutex_unlock(&dinner->run_mutex);
			break ;
		}
		pthread_mutex_unlock(&dinner->run_mutex);
		i = 0;
		while (i < dinner->nr_philos)
		{
			if (!ft_philo_alive(&dinner->philos[i]))
				break ;
			if (ft_all_done(dinner))
				break ;
			i++;
		}
		usleep(900);
	}
	return ;
}

void	run_dinner(t_data *dinner)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < dinner->nr_philos)
	{
		pthread_create(&dinner->philos[i].thread, NULL, 
			&ft_philo_routine, &dinner->philos[i]);
		i++;
	}
	check_dinner(dinner);
	while (j < dinner->nr_philos)
	{
		pthread_join(dinner->philos[j].thread, NULL);
		j++;
	}
}

void	clean_dinner(t_data *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->nr_philos)
	{
		pthread_mutex_destroy(&dinner->philos[i].mutex);
		pthread_mutex_destroy(&dinner->forks[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&dinner->run_mutex);
	pthread_mutex_destroy(&dinner->log_mutex);
	free(dinner->forks);
	free(dinner->philos);
}

int	is_simulation_running(t_data *dinner)
{
	int	result;

	pthread_mutex_lock(&dinner->run_mutex);
	result = dinner->running;
	pthread_mutex_unlock(&dinner->run_mutex);
	return (result);
}
