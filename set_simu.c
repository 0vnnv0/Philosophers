/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_simu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anna <anna@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:23:40 by anna              #+#    #+#             */
/*   Updated: 2024/10/01 14:02:34 by anna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_create_threads(t_simulation *simu)
{
	int	i;

	i = 0;
	while (i < simu->nr_of_philosophers)
	{
		pthread_create(&simu->philos[i].thread, NULL, ft_philo_routine, &simu->philos[i]);
		i++;
	}
}

void	*ft_philo_routine(void *arg)
{
	t_philosopher	*philo;
	//t_simulation	*simu;

	philo = (t_philosopher *)arg;
	//simu = philo->simu;
	while (1)
	{
		ft_status(philo, "is thinking");
		usleep(1000);
	}
	return (NULL);
}

void	ft_status(t_philosopher *philo, char *status)
{
	long long	current_time;

	current_time = ft_gettime() - philo->simu->start_time;
	printf("%lld %d %s\n", current_time, philo->philo_id, status);
}
