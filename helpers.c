/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anna <anna@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:49:07 by anschmit          #+#    #+#             */
/*   Updated: 2024/12/17 11:43:36 by anna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * (long long)1000LL) + (tv.tv_usec / 1000);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	st1;
	unsigned char	st2;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		st1 = (unsigned char)s1[i];
		st2 = (unsigned char)s2[i];
		if (st1 == st2)
		{
			i++;
		}
		else
		{
			return (st1 - st2);
		}
	}
	return (0);
}

void	status(t_simulation *simu, int id, const char *status)
{
	long long	current_time;
	long long	run_time;
	int			run;

	current_time = ft_get_time();
	run_time = current_time - simu->start_time;
	pthread_mutex_lock(&simu->run_mutex);
	run = simu->running;
	pthread_mutex_unlock(&simu->run_mutex);
	pthread_mutex_lock(&simu->log_mutex);
	if (run == 0 && ft_strncmp(status, "died", 4) != 0)
	{
		pthread_mutex_unlock(&simu->log_mutex);
		return ;
	}
	printf("%lld %d %s\n", run_time, id, status);
	pthread_mutex_unlock(&simu->log_mutex);
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
