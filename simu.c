/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anschmit <anschmit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:52:24 by anschmit          #+#    #+#             */
/*   Updated: 2024/12/12 18:15:52 by anschmit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philo_sleep(int ms)
{
	long long	start;

	start = ft_get_time();
	while (ft_get_time() - start < ms)
		usleep(100);
}

void	ft_philo_eat(t_philosopher *philo, t_simulation *simu)
{
	status(philo, "is eating");
	pthread_mutex_lock(&philo->mutex);
	philo->last_meal_time = ft_get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->mutex);
	ft_philo_sleep(simu->time_to_eat);
}

void	*ft_philo_routine(void *arg)
{
	t_philosopher	*philo;
	t_simulation	*simu;

	philo = (t_philosopher *)arg;
	simu = philo->simu;
	while (!simu->simu_end)
	{
		status(philo, "is thinking");
		pthread_mutex_lock(&philo->left_fork->mutex);
		status(philo, "has taken left fork");
		pthread_mutex_lock(&philo->right_fork->mutex);
		status(philo, "has taken right fork");
		ft_philo_eat(philo, simu);
		pthread_mutex_unlock(&philo->left_fork->mutex);
		pthread_mutex_unlock(&philo->right_fork->mutex);
		status(philo, "is sleeping");
		ft_philo_sleep(simu->time_to_sleep);
		if (simu->nr_meals > 0 && philo->meals_eaten >= simu->nr_meals)
			break ;
	}
	return (NULL);
}

// void set_mutex_fork(t_simulation *simu)
// {
//     int i;

//     i = 0;
//     printf("Initializing mutexes and philosopher IDs\n");
//     while (i < simu->nr_philos)
//     {
//         simu->philos[i].philo_id = i + 1;
//         if (pthread_mutex_init(&simu->forks[i].mutex, NULL) != 0)
//         {
//             printf("Failed to initialize mutex for fork %d\n", i);
//             return;
//         }
//         printf("Initialized mutex for fork %d\n", i);
//         i++;
//     }
//     printf("All mutexes initialized\n");
// }

// int set_simulation(t_simulation *simu, int argc, char **argv)
// {
//     printf("Starting set_simulation\n");
    
//     simu->nr_philos = ft_atoi(argv[1]);
//     simu->time_to_die = ft_atoi(argv[2]);
//     simu->time_to_eat = ft_atoi(argv[3]);
//     simu->time_to_sleep = ft_atoi(argv[4]);
    
//     printf("Parsed arguments: philos=%d, die=%d, eat=%d, sleep=%d\n", 
//            simu->nr_philos, simu->time_to_die, simu->time_to_eat, simu->time_to_sleep);
    
//     simu->start_time = ft_get_time();
//     simu->simu_end = 0;
    
//     if (argc == 6)
//     {
//         simu->nr_meals = ft_atoi(argv[5]);
//         printf("Number of meals: %d\n", simu->nr_meals);
//     }
//     else
//         simu->nr_meals = 0;
    
//     printf("Allocating memory for forks\n");
//     simu->forks = malloc(sizeof(t_fork) * simu->nr_philos);
//     if (!simu->forks)
//     {
//         printf("Failed to allocate memory for forks\n");
//         return (1);
//     }
    
//     printf("Allocating memory for philosophers\n");
//     simu->philos = malloc(sizeof(t_philosopher) * simu->nr_philos);
//     if (!simu->philos)
//     {
//         printf("Failed to allocate memory for philosophers\n");
//         free(simu->forks);
//         return (1);
//     }
    
//     set_mutex_fork(simu);
//     // clean_mutex(simu);  // Commented out as it's not defined in the provided code
    
//     printf("set_simulation completed successfully\n");
//     return (0);
// }

void	set_mutex_fork(t_simulation *simu)
{
	int	i;

	i = 0;
	while (i < simu->nr_philos)
	{
		simu->philos[i].philo_id = i + 1;
		pthread_mutex_init(&simu->forks[i].mutex, NULL);
		i++;
	}
}

int	set_simulation(t_simulation *simu, int argc, char **argv)
{
	simu->nr_philos = ft_atoi(argv[1]);
	simu->time_to_die = ft_atoi(argv[2]);
	simu->time_to_eat = ft_atoi(argv[3]);
	simu->time_to_sleep = ft_atoi(argv[4]);
	simu->start_time = ft_get_time();
	simu->simu_end = 0;
	if (argc == 6)
		simu->nr_meals = ft_atoi(argv[5]);
	else
		simu->nr_meals = 0;
	simu->forks = malloc(sizeof(t_fork) * simu->nr_philos);
	if (!simu->forks)
		return (1);
	simu->philos = malloc(sizeof(t_philosopher) * simu->nr_philos);
	if (!simu->philos)
		return (1);
	// set_mutex_fork(simu);
	clean_mutex(simu);
	return (0);
}
