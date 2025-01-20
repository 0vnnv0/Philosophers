/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anschmit <anschmit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:42:42 by anschmit          #+#    #+#             */
/*   Updated: 2025/01/10 16:40:53 by anschmit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_data	t_data;

typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philosopher
{
	int				philo_id;
	int				meals_eaten;
	size_t			last_meal_time;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread;
	pthread_mutex_t	mutex;
	t_data			*dinner; 
}	t_philosopher;

typedef struct s_data
{
	int				nr_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				nr_meals;
	size_t			start_time;
	int				running;
	t_philosopher	*philos;
	t_fork			*forks;
	pthread_mutex_t	run_mutex;
	pthread_mutex_t	log_mutex;
}	t_data;

int			ft_atoi(const char *str);
int			ft_isnumber(char *argv);
int			ft_validate(int argc, char **argv);
void		init_philosophers(t_data *dinner);
void		ft_create_threads(t_data *dinner);
void		*ft_philo_routine(void *arg);
int			ft_philo_eat(t_philosopher *philo);
size_t		time_ms(void);
void		status(t_data *dinner, int id, const char *status);
int			clean_mutex(t_data *dinner);
void		ft_join_threads(t_data *dinner);
void		*death_check(void *arg);
void		clean_dinner(t_data *dinner);
int			ft_all_done(t_data *dinner);
int			ft_philo_alive(t_philosopher *philo);
void		run_dinner(t_data *dinner);
void		init_dinner(t_data *dinner, int argc, char **argv, size_t st);
int			is_simulation_running(t_data *dinner);
