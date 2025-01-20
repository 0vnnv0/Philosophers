/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anschmit <anschmit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:49:07 by anschmit          #+#    #+#             */
/*   Updated: 2025/01/10 16:30:49 by anschmit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	time_ms(void)
{
	struct timeval	tv;
	size_t			ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms);
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

void	status(t_data *dinner, int id, const char *status)
{
	size_t	current_time;
	size_t	run_time;
	int		run;

	current_time = time_ms();
	run_time = current_time - dinner->start_time;
	pthread_mutex_lock(&dinner->log_mutex);
	pthread_mutex_lock(&dinner->run_mutex);
	run = dinner->running;
	pthread_mutex_unlock(&dinner->run_mutex);
	if (run || ft_strncmp(status, "died", 4) == 0)
	{
		printf("%zu %d %s\n", run_time, id, status);
	}
	pthread_mutex_unlock(&dinner->log_mutex);
}

int	ft_atoi(const char *str)
{
	int	nbr;

	nbr = 0;
	while (*str == ' ' || *str == '\t' || *str == '+')
		str++;
	if (*str == '-')
		return (0);
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + (*str - 48);
		str++;
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
