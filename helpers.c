/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anschmit <anschmit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:49:07 by anschmit          #+#    #+#             */
/*   Updated: 2024/12/12 17:08:21 by anschmit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	status(t_philosopher *philo, char *status)
{
	long long	current_time;

	current_time = ft_get_time() - philo->simu->start_time;
	printf("%lld %d %s\n", current_time, philo->philo_id, status);
}

int	ft_atoi(char *str)
{
	int	nbr;

	nbr = 0;
	while (*str == ' ' || *str == '\t' || *str == '+')
		str++;
	if (*str == '-')
		return (0);
	while (*str != '\0')
	{
		if (*str >= '0' && *str <= '9')
		{
			nbr = nbr * 10 + (*str - 48);
			str++;
		}
	}
	return (nbr);
}

int	ft_isnumber(char *nbr)
{
	while (*nbr)
	{
		if (*nbr >= '0' && *nbr <= '9')
			nbr++;
		else
			return (0);
	}
	return (1);
}
