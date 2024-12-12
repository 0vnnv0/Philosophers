/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anschmit <anschmit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:42:17 by anschmit          #+#    #+#             */
/*   Updated: 2024/12/12 18:15:54 by anschmit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_validate(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		printf("Wrong number of arguments!\n");
		return (0);
	}
	if (ft_atoi(argv[1]) == 0)
		return (printf("No philosophers found!\n"), 0);
	if (argc == 6 && ft_atoi(argv[5]) == 0)
		return (printf("No food to eat!\n"), 0);
	while (i < argc)
	{
		if (!ft_isnumber(argv[i]))
			return (printf("invalid arguments!\n"), 0);
		i++;
	}
	return (1);
}

void	set_forks(t_simulation *simu)
{
	int	i;

	i = 0;
	while (i < simu->nr_philos)
	{
		if (pthread_mutex_init(&simu->forks[i].mutex, NULL) != 0)
		{
			printf("Failed to initialize mutex for fork %d\n", i);
			exit(1);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_simulation	simu;
	pthread_t	death_checker;

	if (ft_validate(argc, argv) == 0)
		return (1);
	set_simulation(&simu, argc, argv);
	set_forks(&simu);
	set_philosophers(&simu);
	pthread_create(&death_checker, NULL, death_check, & simu);
	ft_create_threads(&simu);
	ft_join_threads(&simu);
	return (0);
}
