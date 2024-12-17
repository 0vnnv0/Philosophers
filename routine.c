
#include "philo.h"

void	timer(t_philosopher *philo, long ms)
{
	long long	start;
	long long	current;
	long long	end;

	start = ft_get_time();
	current = start;
	end = start + ms;
	while (current < end)
	{
		usleep(100);
		if (current - philo->last_meal_time > philo->simu->time_to_die)
			break ;
		current = ft_get_time();
	}
}

void	ft_take_forks(t_philosopher *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		status(philo->simu, philo->philo_id, "has taken a fork");
		usleep(100);
		pthread_mutex_lock(&philo->right_fork->mutex);
		status(philo->simu, philo->philo_id, "has taken a fork");
	}
	else
	{
		usleep(100);
		pthread_mutex_lock(&philo->right_fork->mutex);
		status(philo->simu, philo->philo_id, "has taken a fork");
		usleep(100);
		pthread_mutex_lock(&philo->left_fork->mutex);
		status(philo->simu, philo->philo_id, "has taken a fork");
	}
	return ;
}

void	ft_philo_think(t_philosopher *philo)
{
	long	eat;
	long	think;
	long	sleep;

	if (philo->simu->nr_philos % 2 == 0)
		return ;
	eat = philo->simu->time_to_eat;
	sleep = philo->simu->time_to_sleep;
	think = (eat * 2) - sleep;
	if (think < 0 || philo->meals_eaten == 0)
		think = 0;
	timer(philo, think * 0.3);
}

int	ft_philo_eat(t_philosopher *philo)
{
	if (philo->simu->nr_philos == 1)
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		status(philo->simu, philo->philo_id, "has taken a fork");
		pthread_mutex_unlock(&philo->left_fork->mutex);
		return (0);
	}
	ft_take_forks(philo);
	status(philo->simu, philo->philo_id, "is eating");
	pthread_mutex_lock(&philo->mutex);
	philo->last_meal_time = ft_get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->mutex);
	timer(philo, philo->simu->time_to_eat);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
	return (1);
}

void	*ft_philo_routine(void *arg)
{
	t_philosopher	*philo;
	t_simulation	*simu;

	philo = (t_philosopher *)arg;
	simu = philo->simu;
	while (1)
	{
		pthread_mutex_lock(&simu->run_mutex);
		if (!simu->running)
		{
			pthread_mutex_unlock(&simu->run_mutex);
			break ;
		}
		pthread_mutex_unlock(&simu->run_mutex);
		if (!simu->nr_philos != 1)
		{
			status(simu, philo->philo_id, "is thinking");
			ft_philo_think(philo);
		}
		if (!ft_philo_eat(philo) || ft_philos_full(simu))
			return (NULL);
		status(simu, philo->philo_id, "is_sleeping");
		timer(philo, simu->time_to_sleep);
	}
	return (NULL);
}
