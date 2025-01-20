/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anschmit <anschmit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:03:52 by anschmit          #+#    #+#             */
/*   Updated: 2025/01/10 14:09:20 by anschmit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_all_done(t_data *dinner)
{
	int	i;
	int	done;

	i = 0;
	done = 1;
	if (dinner->nr_meals == -1)
		return (0);
	while (i < dinner->nr_philos)
	{
		pthread_mutex_lock(&dinner->philos[i].mutex);
		if (dinner->philos[i].meals_eaten < dinner->nr_meals)
			done = 0;
		pthread_mutex_unlock(&dinner->philos[i].mutex);
		i++;
	}
	if (done == 1)
	{
		pthread_mutex_lock(&dinner->run_mutex);
		dinner->running = 0;
		pthread_mutex_unlock(&dinner->run_mutex);
	}
	return (done);
}

int	ft_philo_alive(t_philosopher *philo)
{
	size_t	foodless_time;

	pthread_mutex_lock(&philo->mutex);
	foodless_time = time_ms() - philo->last_meal_time;
	if (foodless_time > philo->dinner->time_to_die)
	{
		pthread_mutex_lock(&philo->dinner->run_mutex);
		philo->dinner->running = 0;
		pthread_mutex_unlock(&philo->dinner->run_mutex);
		status(philo->dinner, philo->philo_id, "died");
		pthread_mutex_unlock(&philo->mutex);
		return (0);
	}
	if (philo->meals_eaten == philo->dinner->nr_meals)
	{
		pthread_mutex_unlock(&philo->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->mutex);
	return (1);
}
