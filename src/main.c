#include "../philo.h"
#include <pthread.h>


void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->mutex);
	what_time(philo->args);
	philo->last_eat = philo->args->time;
	if (philo->args->die == 0)
	{
		printf("%zu %d is eating\n", philo->args->time, philo->philo_nb);
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
			
			pthread_mutex_lock(philo->right_fork);
			pthread_mutex_lock(&philo->args->mutex);
			what_time(philo->args);
			if (philo->args->die == 0)
			{
				printf("%zu %d has taken a fork\n", philo->args->time, philo->philo_nb);
			}
			pthread_mutex_unlock(&philo->args->mutex);
			pthread_mutex_lock(philo->left_fork);	
			pthread_mutex_lock(&philo->args->mutex);
			what_time(philo->args);
			if (philo->args->die == 0)
			{
				printf("%zu %d has taken a fork\n", philo->args->time, philo->philo_nb);
			}
			pthread_mutex_unlock(&philo->args->mutex);
		}
		else
		{
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(&philo->args->mutex);
			what_time(philo->args);
			if (philo->args->die == 0)
			{
				printf("%zu %d has taken a fork\n", philo->args->time, philo->philo_nb);
			}
			pthread_mutex_unlock(&philo->args->mutex);
			pthread_mutex_lock(philo->right_fork);	
			pthread_mutex_lock(&philo->args->mutex);
			what_time(philo->args);
			if (philo->args->die == 0)
			{
				printf("%zu %d has taken a fork\n", philo->args->time, philo->philo_nb);
			}
			pthread_mutex_unlock(&philo->args->mutex);
		}
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);	
	}
}
void	*rou(t_philo *philo)
{
	if (philo->philo_nb % 2 != 0)
		my_usleep(philo->time_to_eat, philo->args);
	while (1)
	{
		lock_unlock_fork(philo, 1);
		eat(philo);
		lock_unlock_fork(philo, 0);
		pthread_mutex_lock(&philo->args->mutex);
		what_time(philo->args);
		if (philo->args->die == 0)
		{
			printf("%zu %d is sleeping\n", philo->args->time, philo->philo_nb);
		}
		pthread_mutex_unlock(&philo->args->mutex);
		my_usleep(philo->time_to_sleep, philo->args);
		pthread_mutex_lock(&philo->args->mutex);
		what_time(philo->args);
		if (philo->args->die == 0)
			printf("%zu %d is thinking\n", philo->args->time, philo->philo_nb);
		pthread_mutex_unlock(&philo->args->mutex);
		if (philo->args->die == 1)
		{
			return (NULL);
		}
	}
	return (NULL);
}

int	create_threads(t_args *args, void *rou)
{
	int	i;

	i = 0;
	pthread_mutex_init(&args->mutex, NULL);
	while (i < args->nb_philo)
	{
		if (pthread_create(&args->philo[i]->thread ,NULL, rou, args->philo[i])) 
		{
		    fprintf(stderr, "Erreur lors de la création du thread\n");
		    return (1);
		}
		i++;
    }
	i = 0;
	while (1)
	{
		while (i < args->nb_philo)
		{
			pthread_mutex_lock(&args->mutex);
			what_time(args);
			pthread_mutex_unlock(&args->mutex);
			if (args->time - args->philo[i]->last_eat  > args->philo[i]->time_to_die)
			{
				args->die = 1;
				pthread_mutex_lock(&args->mutex);
				what_time(args);
				printf("%zu %d died\n", args->time, i + 1);
				pthread_mutex_unlock(&args->mutex);
				break ;
			}
			i++;
		}
		if (args->die == 1)
		{
			for (int j = 0; j < args->nb_philo; j++)
				pthread_join(args->philo[j]->thread, NULL);
			break ;
		}
		i = 0;
	}

	pthread_mutex_destroy(&args->mutex);
	return (0);
}

int	create_fork(t_args *args)
{
	int				i;
	pthread_mutex_t *forks;
	
	i = 0;

	forks = calloc(sizeof(pthread_mutex_t), args->nb_philo);
	while (i < args->nb_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) == -1)
			return(1);
		i++;
	}
	i = 0;
	while (i < args->nb_philo)
	{
		args->philo[i]->right_fork = &forks[i];
		if (i != 0)
			args->philo[i]->left_fork = &forks[i -1];
		else if (i == 0)
			args->philo[i]->left_fork = &forks[args->nb_philo - 1];
		i++;
	}
	return (0);
}


void	fill_value(char **av, t_args *args, int ac)
{
	int	i;

	i = 0;

	while (i < args->nb_philo)
	{
		args->philo[i] = calloc (sizeof(t_philo), 1);
		if (args->philo[i] == NULL)
		{
			printf("ELIZA\n");
			return ;
		}
		args->philo[i]->args = args;
		args->philo[i]->philo_nb = i + 1;
		args->philo[i]->time_to_die = ft_atol(av[2]);
		args->philo[i]->time_to_eat = ft_atol(av[3]);
		args->philo[i]->time_to_sleep = ft_atol(av[4]);
		if (ac == 6)
			args->philo[i]->each_eat = ft_atol(av[5]);
		else
			args->philo[i]->each_eat = -1;
		i++;
	}
	create_fork(args);
	i = 0;
	what_first_time(args);
	create_threads(args, rou);
}

int	check_arg(char **av, int ac)
{
	int		i;
	long	atol;
	int		j;
	
	atol = 0;
	j = 0;
	i = 1;
	while (av[i] && i <= ac)
	{
		while (av[i][j])
		{
			if (ft_isdigit(av[i][j]) == 1)
				j++;
			else
				return (0);
		}
		atol = ft_atol(av[i]);
		if ((atol > INT_MAX || atol <= 0) || (ft_strlen(av[i]) >= 11))
			return (0);
		j = 0;
		i++;
	}
	return (1);
}


int main (int ac, char **av)
{
	t_args			args;
	int				i;
	
	args = (t_args){0};
	i = 0;
	if (ac == 5 || ac == 6)
	{
		if (check_arg(av, ac) == 1)
		{
			args.nb_philo = ft_atol(av[1]);
			args.philo = calloc(sizeof(t_philo *), args.nb_philo);
			if (args.philo == NULL)
				return (printf("VOLKAN\n"));
			fill_value(av, &args, ac);
		}
		else
		{
			printf("args error\n");
			return (-1);
		}
	}
	else
		printf ("non\n");
	while (i < args.nb_philo)
	{
		free(args.philo[i]);
		i++;
	}
	free (args.philo);
}
