#include "../philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->mutex);
	if (philo->args->die == 0)
	{
		philo->last_eat = what_time(philo->args);
		printf("%zu %d is eating\n", what_time(philo->args), philo->philo_nb);
		philo->nb_eat++;
	}
	pthread_mutex_unlock(&philo->args->mutex);
	my_usleep (philo->time_to_eat, philo->args);
}

void	lock_unlock_fork(t_philo *philo, int lock)
{
	if (lock)
	{
		if (philo->philo_nb == 1)
		{
			
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(&philo->args->mutex);
			if (philo->args->die == 0)
				printf("%zu %d has taken a fork\n", what_time(philo->args), philo->philo_nb);
			pthread_mutex_unlock(&philo->args->mutex);
			pthread_mutex_lock(philo->right_fork);	
			pthread_mutex_lock(&philo->args->mutex);
			if (philo->args->die == 0)
				printf("%zu %d has taken a fork\n", what_time(philo->args), philo->philo_nb);
			pthread_mutex_unlock(&philo->args->mutex);
		}
		else
		{
			pthread_mutex_lock(philo->right_fork);
			pthread_mutex_lock(&philo->args->mutex);
			if (philo->args->die == 0)
				printf("%zu %d has taken a fork\n", what_time(philo->args), philo->philo_nb);
			pthread_mutex_unlock(&philo->args->mutex);
			pthread_mutex_lock(philo->left_fork);	
			pthread_mutex_lock(&philo->args->mutex);
			if (philo->args->die == 0)
				printf("%zu %d has taken a fork\n", what_time(philo->args), philo->philo_nb);
			pthread_mutex_unlock(&philo->args->mutex);
		}
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);	
	}
}

void	my_sleep(t_philo *philo)
{
	if (philo->args->die == 0)
		printf("%zu %d is sleeping\n", what_time(philo->args), philo->philo_nb);
	pthread_mutex_unlock(&philo->args->mutex);
	my_usleep(philo->time_to_sleep, philo->args);
	pthread_mutex_lock(&philo->args->mutex);
	if (philo->args->die == 0)
		printf("%zu %d is thinking\n", what_time(philo->args), philo->philo_nb);
	pthread_mutex_unlock(&philo->args->mutex);
	if (philo->time_to_die - (philo->time_to_eat + philo->time_to_sleep) >= 1)
		my_usleep(philo->time_to_die
			- (philo->time_to_eat + philo->time_to_sleep) - 20, philo->args);
	else
		usleep(10);
}

void	*rou(t_philo *philo)
{
	if (philo->philo_nb % 2 != 0)
		my_usleep(philo->time_to_eat / 2, philo->args);
	while (1)
	{
		lock_unlock_fork(philo, 1);
		eat(philo);
		lock_unlock_fork(philo, 0);
		pthread_mutex_lock(&philo->args->mutex);
		my_sleep(philo);
		pthread_mutex_lock(&philo->args->mutex);
		if (philo->args->die == 1 || philo->args->all_eat == 1)
		{
			pthread_mutex_unlock(&philo->args->mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->args->mutex);
	}
	return (NULL);
}
