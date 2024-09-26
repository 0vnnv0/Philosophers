/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anschmit <anschmit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:31:15 by anna              #+#    #+#             */
/*   Updated: 2024/09/26 14:20:35 by anschmit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_gettime(void)
{
	struct timeval	tv;
	long long		timestamp;

	gettimeofday(&tv, NULL);
	timestamp = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
	return (timestamp);
}

int	ft_atoi(char *nr)
{
	int	result;

	result = 0;
	while (*nr == ' ' || *nr == '	' || *nr == '+')
		nr++;
	if (*nr == '-')
		return (0);
	if (*nr >= '0' && *nr <= '9')
	{
		result = result * 10 + (*nr - 48);
		nr++;
	}
	return (result);
}

int	ft_isnumber(char *nr)
{
	while (*nr)
	{
		if (*nr >= '0' && *nr <= '9')
			nr++;
		else
			return (0);
	}
	return (1);
}