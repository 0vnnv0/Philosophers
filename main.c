/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anna <anna@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:42:17 by anschmit          #+#    #+#             */
/*   Updated: 2024/12/17 15:16:05 by anna             ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_simulation	simu;

	if (ft_validate(argc, argv) == 0)
		return (1);
	set_simulation(&simu, argc, argv);
	set_philosophers(&simu);
//	run_simu(&simu);
	clean_simu(&simu);
	return (0);
}
