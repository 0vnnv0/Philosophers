/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anschmit <anschmit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:27:54 by anschmit          #+#    #+#             */
/*   Updated: 2025/01/10 16:40:22 by anschmit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	timer(t_philosopher *philo, long ms)
{
	size_t	start;
	size_t	current;
	size_t	end;

	start = time_ms();
	current = start;
	end = start + ms;
	while (current < end)
	{
		usleep(100);
		if (current - philo->last_meal_time > philo->dinner->time_to_die)
			break ;
		current = time_ms();
	}
}

void	ft_take_forks(t_philosopher *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		status(philo->dinner, philo->philo_id, "has taken a fork");
		usleep(100);
		pthread_mutex_lock(&philo->right_fork->mutex);
		status(philo->dinner, philo->philo_id, "has taken a fork");
	}
	else
	{
		usleep(100);
		pthread_mutex_lock(&philo->right_fork->mutex);
		status(philo->dinner, philo->philo_id, "has taken a fork");
		usleep(100);
		pthread_mutex_lock(&philo->left_fork->mutex);
		status(philo->dinner, philo->philo_id, "has taken a fork");
	}
	return ;
}

void	ft_philo_think(t_philosopher *philo)
{
	long	eat;
	long	think;
	long	sleep;

	if (philo->dinner->nr_philos % 2 == 0)
		return ;
	eat = philo->dinner->time_to_eat;
	sleep = philo->dinner->time_to_sleep;
	think = (eat * 2) - sleep;
	if (think < 0 || philo->meals_eaten == 0)
		think = 0;
	timer(philo, think * 0.3);
}

int	ft_philo_eat(t_philosopher *philo)
{
	if (philo->dinner->nr_philos == 1)
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		status(philo->dinner, philo->philo_id, "has taken a fork");
		pthread_mutex_unlock(&philo->left_fork->mutex);
		return (0);
	}
	ft_take_forks(philo);
	status(philo->dinner, philo->philo_id, "is eating");
	pthread_mutex_lock(&philo->mutex);
	philo->last_meal_time = time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->mutex);
	timer(philo, philo->dinner->time_to_eat);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
	return (1);
}

void	*ft_philo_routine(void *arg)
{
	t_philosopher	*philo;
	t_data			*dinner;

	philo = (t_philosopher *)arg;
	dinner = philo->dinner;
	while (1)
	{
		if (!is_simulation_running(dinner))
			break ;
		if (dinner->nr_philos != 1)
		{
			status(dinner, philo->philo_id, "is thinking");
			ft_philo_think(philo);
		}
		if (!is_simulation_running(dinner))
			break ;
		if (!ft_philo_eat(philo) || ft_all_done(dinner))
			break ;
		if (!is_simulation_running(dinner))
			break ;
		status(dinner, philo->philo_id, "is sleeping");
		timer(philo, dinner->time_to_sleep);
	}
	return (NULL);
}

// void	*ft_philo_routine(void *arg)
// {
// 	t_philosopher	*philo;
// 	t_data			*dinner;

// 	philo = (t_philosopher *)arg;
// 	dinner = philo->dinner;
// 	while (1)
// 	{
// 		pthread_mutex_lock(&dinner->run_mutex);
// 		if (!dinner->running)
// 		{
// 			pthread_mutex_unlock(&dinner->run_mutex);
// 			break ;
// 		}
// 		pthread_mutex_unlock(&dinner->run_mutex);
// 		if (dinner->nr_philos != 1)
// 		{
// 			status(dinner, philo->philo_id, "is thinking");
// 			ft_philo_think(philo);
// 		}
// 		if (!ft_philo_eat(philo) || ft_all_done(dinner))
// 			return (NULL);
// 		status(dinner, philo->philo_id, "is_sleeping");
// 		timer(philo, dinner->time_to_sleep);
// 	}
// 	return (NULL);
// }
