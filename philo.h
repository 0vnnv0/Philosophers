/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anschmit <anschmit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:42:42 by anschmit          #+#    #+#             */
/*   Updated: 2024/12/12 18:04:40 by anschmit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_simulation t_simulation;

typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philosopher
{
	int				philo_id;
	int				meals_eaten;
	long long		last_meal_time;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread;
	pthread_mutex_t	mutex;
	t_simulation	*simu; 
}	t_philosopher;

typedef struct s_simulation
{
	int				nr_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nr_meals;
	long long		start_time;
	int				simu_end;
	t_philosopher	*philos;
	t_fork			*forks;
	pthread_t		death_checker;
}	t_simulation;

int			ft_atoi(char *str);
int			ft_isnumber(char *argv);
int			ft_validate(int argc, char **argv);
int			set_simulation(t_simulation *simu, int argc, char **argv);
void		set_philosophers(t_simulation *simu);
void		ft_create_threads(t_simulation *simu);
void		*ft_philo_routine(void *arg);
long long	ft_get_time(void);
void		status(t_philosopher *philo, char *status);
int			clean_mutex(t_simulation *simu);
void		ft_join_threads(t_simulation *simu);
void		*death_check(void *arg);
