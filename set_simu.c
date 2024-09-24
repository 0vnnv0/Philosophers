/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_simu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anna <anna@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:23:40 by anna              #+#    #+#             */
/*   Updated: 2024/09/24 15:23:55 by anna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_set_simu(t_simulation *simulation, int argc, char **argv)
{
		simulation->number_of_philosophers = ft_atoi(argv[1]);
		simulation->time_to_die = ft_atoi(argv[2]);
		simulation->time_to_eat = ft_atoi(argv[3]);
		simulation->time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			simulation->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
		else
			simulation->number_of_times_each_philosopher_must_eat = 0;
}
