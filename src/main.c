#include "../philo.h"
#include <strings.h>

void	fill_value(int i, long atol, t_args *args)
{
	if (i == 1)
		args->nb_philo = atol;
	if (i == 2)
		args->time_to_die = atol;
	if (i == 3)
		args->time_to_eat = atol;
	if (i == 4)
		args->time_to_sleep = atol;
	if (i == 5)
		args->each_eat = atol;
}


int	check_arg(char **av, int ac, t_args *args)
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
		else
			fill_value (i, atol, args);
		j = 0;
		i++;
	}
	return (1);
}


void	*print_test_odd(void *arg)
{
	t_args *args = (t_args *)arg;
	int	i = args->philo_n;
	
	if (i % 2 == 0)
	{
		pthread_mutex_lock(&args->mutex);
	    printf("%i est pair\n", i);
	    pthread_mutex_unlock(&args->mutex); 
	}
	else
	{
		pthread_mutex_lock(&args->mutex);
	    printf("%i est impair\n", i);
	    pthread_mutex_unlock(&args->mutex); 
	}
	return NULL;
}


int	test_thread(t_args *args)
{
	pthread_t	thread[args->nb_philo];
	int	i = 0;

	pthread_mutex_init(&args->mutex, NULL);

	printf("nb = %i\n", args->nb_philo);
	while (i < args->nb_philo)
	{
		pthread_mutex_lock(&args->mutex);
		args->philo_n = i + 1;
		pthread_mutex_unlock(&args->mutex);
		
		if (pthread_create(&thread[i], NULL, print_test_odd, args)) 
		{
			fprintf(stderr, "Erreur lors de la création du thread\n");
			return 1;
		}
        i++;
    }
	for (int j = 0; j < args->nb_philo; j++)
        pthread_join(thread[j], NULL);
	pthread_mutex_destroy(&args->mutex);
	return (0);
}

int main (int ac, char **av)
{
	t_args		*args;

	args = calloc(sizeof(t_args) + sizeof(pthread_mutex_t), 1);
	if (ac == 5 || ac == 6)
	{
		if (check_arg(av, ac, args) == 0)
		{
			free (args);
			printf("args error\n");
			return (-1);
		}
		else
		{
			test_thread(args);
		}
	}
	else
		printf ("non\n");
	free (args);
}
