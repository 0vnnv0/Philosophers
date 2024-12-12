/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anschmit <anschmit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:03:52 by anschmit          #+#    #+#             */
/*   Updated: 2024/12/12 18:11:55 by anschmit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death_check(void *arg)
{
	t_simulation	*simu;
	int				i;

	simu = (t_simulation *)arg;
	i = 0;
	while (!simu->simu_end)
	{
		while (i < simu->nr_philos)
		{
			pthread_mutex_lock(&simu->philos[i].mutex);
			if (ft_get_time() - simu->philos[i].last_meal_time > simu->time_to_die)
			{
				status(&simu->philos[i], "died");
				simu->simu_end = 1;
				pthread_mutex_unlock(&simu->philos[i].mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&simu->philos[i].mutex);
		}
		usleep(1000);
	}
	return (NULL);
}
