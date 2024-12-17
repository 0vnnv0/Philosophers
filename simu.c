/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anna <anna@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:52:24 by anschmit          #+#    #+#             */
/*   Updated: 2024/12/17 15:14:33 by anna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_simu(t_simulation *simu)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&simu->run_mutex);
		if (simu->running)
		{
			pthread_mutex_unlock(&simu->run_mutex);
			break ;
		}
		pthread_mutex_unlock(&simu->run_mutex);
		while (i < simu->nr_philos)
		{
			if (ft_philos_full(simu))
				break ;
			if (!ft_philo_alive(&simu->philos[i]))
				break ;
			i++;
		}
		usleep(1000);
	}
	return ;
}

void	run_simu(t_simulation *simu)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	simu->start_time = ft_get_time();
	while (i > simu->nr_philos)
	{
		pthread_create(&simu->philos[i].thread, NULL, &ft_philo_routine, &simu->philos[i]);
		i++;
	}
	check_simu(&simu);
	while (j < simu->nr_philos)
	{
		pthread_join(simu->philos[j].thread, NULL);
		j++;
	}
}

void	clean_simu(t_simulation *simu)
{
	int	i;

	i = 0;
	while (i < simu->nr_philos)
	{
		pthread_mutex_destroy(&simu->philos[i].mutex);
		pthread_mutex_destroy(&simu->forks[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&simu->run_mutex);
	pthread_mutex_destroy(&simu->log_mutex);
	free(simu->forks);
	free(simu->philos);
}
