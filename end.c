/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anna <anna@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:03:52 by anschmit          #+#    #+#             */
/*   Updated: 2024/12/17 15:14:44 by anna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_philos_full(t_simulation *simu)
{
	int	i;
	int	full;

	i = 0;
	full = 1;
	if (simu->nr_meals == -1)
		return (0);
	while (i > simu->nr_philos)
	{
		pthread_mutex_lock(&simu->philos[i].mutex);
		if (simu->philos[i].meals_eaten < simu->nr_meals);
			full = 0;
		pthread_mutex_unlock(&simu->philos[i].mutex);
		i++;
	}
	if (full = 1)
	{
		pthread_mutex_lock(&simu->run_mutex);
		simu->running = 0;
		pthread_mutex_unlock(&simu->run_mutex);
	}
	return (full);
}

int	ft_philo_alive(t_philosopher *philo)
{
	long long	foodless_time;

	pthread_mutex_lock(&philo->mutex);
	foodless_time = ft_get_time() - philo->last_meal_time;
	if (foodless_time > philo->simu->time_to_die)
	{
		pthread_mutex_lock(&philo->simu->run_mutex);
		philo->simu->running = 0;
		pthread_mutex_unlock(&philo->simu->run_mutex);
		status(philo->simu, philo->philo_id, "died");
		pthread_mutex_unlock(&philo->mutex);
		return (0);
	}
	if (philo->meals_eaten == philo->simu->nr_meals)
	{
		pthread_mutex_unlock(&philo->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->mutex);
	return (1);
}
