/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anschmit <anschmit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:01:38 by anschmit          #+#    #+#             */
/*   Updated: 2025/01/10 16:41:43 by anschmit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutex(t_data *dinner)
{
	pthread_mutex_init(&dinner->run_mutex, NULL);
	pthread_mutex_init(&dinner->log_mutex, NULL);
}

int	init_mutex_fork_recursive(t_data *dinner, int i)
{
	if (i >= dinner->nr_philos)
		return (0);
	if (pthread_mutex_init(&dinner->forks[i].mutex, NULL) != 0)
	{
		while (--i >= 0)
			pthread_mutex_destroy(&dinner->forks[i].mutex);
		return (-1);
	}
	return (init_mutex_fork_recursive(dinner, i + 1));
}

int	init_mutex_fork(t_data *dinner)
{
	return (init_mutex_fork_recursive(dinner, 0));
}

// void	init_mutex_fork(t_data *dinner)
// {
// 	int	i;

// 	i = 0;
// 	while (i < dinner->nr_philos)
// 	{
// 		// dinner->philos[i].philo_id = i + 1;
// 		if (pthread_mutex_init(&dinner->forks[i].mutex, NULL) != 0)
// 			printf("Error, mutex failed\n");
// 		i++;
// 	}
// }

void	init_dinner(t_data *dinner, int argc, char **argv, size_t st)
{
	dinner->nr_philos = ft_atoi(argv[1]);
	dinner->time_to_die = ft_atoi(argv[2]);
	dinner->time_to_eat = ft_atoi(argv[3]);
	dinner->time_to_sleep = ft_atoi(argv[4]);
	dinner->running = 1;
	dinner->start_time = st;
	init_mutex(dinner);
	if (argc == 6)
		dinner->nr_meals = ft_atoi(argv[5]);
	else
		dinner->nr_meals = -1;
	dinner->forks = malloc(sizeof(t_fork) * dinner->nr_philos);
	if (!dinner->forks)
		return ;
	dinner->philos = malloc(sizeof(t_philosopher) * dinner->nr_philos);
	if (!dinner->philos)
		return ;
	init_mutex_fork(dinner);
	init_philosophers(dinner);
}

void	init_philosophers(t_data *dinner)
{
	int	i;

	i = -1;
	while (++i < dinner->nr_philos)
	{
		dinner->philos[i].philo_id = i + 1;
		dinner->philos[i].meals_eaten = 0;
		dinner->philos[i].last_meal_time = time_ms();
		dinner->philos[i].left_fork = &dinner->forks[i];
		if (i == dinner->nr_philos - 1)
			dinner->philos[i].right_fork = &dinner->forks[0];
		else
			dinner->philos[i].right_fork = &dinner->forks[i + 1];
		dinner->philos[i].dinner = dinner;
		pthread_mutex_init(&dinner->philos[i].mutex, NULL);
	}
	run_dinner(dinner);
}
