/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anna <anna@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:46:41 by anna              #+#    #+#             */
/*   Updated: 2024/10/01 14:00:05 by anna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

typedef struct s_simulation	t_simulation;

typedef struct s_fork
{
	int	fork_id;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct	s_philosopher
{
	int					philo_id;
	t_fork				*left_fork;
	t_fork				*right_fork;
	long long 			last_meal_time;
	int 				meals_eaten;
	pthread_t			thread;
	t_simulation		*simu;
}	t_philosopher;

typedef struct s_simulation
{
	int	nr_of_philosophers;
	int time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nr_of_times_each_philosopher_must_eat;
	long long	start_time;
	t_philosopher	*philos;
	t_fork			*forks;
}	t_simulation;

int			is_valid(int argc, char **argv);
int			ft_atoi(char *nr);
int			ft_isnumber(char *nr);
void		ft_set_simu(t_simulation *simu, int argc, char **argv);
void		ft_set_philos(t_simulation *simu);
long long	ft_gettime(void);
void		ft_create_threads(t_simulation *simu);
void		ft_status(t_philosopher *philo, char *status);
void		*ft_philo_routine(void *arg);





