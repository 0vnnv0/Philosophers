/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anna <anna@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:11:52 by anna              #+#    #+#             */
/*   Updated: 2024/09/25 14:38:20 by anna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_valid(int argc, char **argv)
{
	int	i;

	i = 1;
	if (ft_atoi(argv[1]) == 0)
	{
		printf("No philosophers found!\n");
		return (0);
	}
	if (argc == 6 && ft_atoi(argv[5]) == 0)
	{
		printf("No food to eat!\n");
		return (0);
	}
	while (argc > 1)
	{
		if (!ft_isnumber(argv[i]))
		{
			printf("Invalid arguments!\n");
			return (0);
		}
		argc--;
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_simulation	new_simulation;

	if (argc != 5 && argc != 6)
	{
		printf("Wrong number of arguments!\n");
		return (1);
	}
	else
	{
		if (is_valid(argc, argv))
		{
			ft_set_simu(&new_simulation, argc, argv);
		//	ft_set_philos(&new_simulation);
		}		
	}
	return (0);
}
