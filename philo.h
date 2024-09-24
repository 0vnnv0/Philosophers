/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anna <anna@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:46:41 by anna              #+#    #+#             */
/*   Updated: 2024/09/24 15:16:32 by anna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef struct	s_philosopher
{
	int	id;
	struct s_simulation *simu;
	
}	t_philosopher;

typedef struct s_simulation
{
	int	number_of_philosophers;
	int time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
}	t_simulation;

int		is_valid(int argc, char **argv);
int		ft_atoi(char *nr);
int		ft_isnumber(char *nr);
void	ft_set_simu(t_simulation *simulation, int argc, char **argv);

