/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroualid <aroualid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:46:48 by aroualid          #+#    #+#             */
/*   Updated: 2024/10/10 22:25:28 by aroualid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <pthread.h>

int	check_eat(t_args *args)
{
	int	j;

	j = 0;
	while (j < args->nb_philo)
	{
		if (args->philo[j]->nb_eat < args->philo[j]->each_eat)
			return (0);
		j++;
	}
	if (j == args->nb_philo)
	{
		args->all_eat = 1;
		printf("all philosophers have eaten\n");
		pthread_mutex_unlock(&args->mutex);
		return (1);
	}
	return (0);
}

void	check_dead(t_args *args, int i)
{
	args->die = 1;
	printf("%zu %d died\n", what_time(args), i + 1);
	pthread_mutex_unlock(&args->mutex);
	return ;
}

void	monitoring(t_args *args)
{
	int	i;

	i = 0;
	while (1)
	{
		while (i < args->nb_philo)
		{
			pthread_mutex_lock(&args->mutex);
			if (what_time(args) - args->philo[i]->last_eat
				>= args->philo[i]->time_to_die)
				return (check_dead(args, i));
			if (args->philo[i]->each_eat != -1 && check_eat(args) == 1)
				return ;
			pthread_mutex_unlock(&args->mutex);
			i++;
		}
		my_usleep(500, args);
		i = 0;
	}
}

void	join_dead(t_args *args)
{
	int	j;

	j = 0;
	if (args->die == 1 || args->all_eat == 1)
	{
		while (j < args->nb_philo)
		{
			if (pthread_join(args->philo[j]->thread, NULL) != 0)
				break ;
			j++;
		}
		free_philo(args);
		return ;
	}
}

int	create_threads(t_args *args, void *rou)
{
	int	i;

	i = 0;
	pthread_mutex_init(&args->mutex, NULL);
	while (i < args->nb_philo)
	{
		if (pthread_create(&args->philo[i]->thread, NULL, rou, args->philo[i]))
		{
			printf("Erreur lors de la création du thread\n");
			return (1);
		}
		i++;
	}
	i = 0;
	my_usleep(args->philo[0]->time_to_die, args);
	monitoring(args);
	join_dead(args);
	pthread_mutex_destroy(&args->mutex);
	return (0);
}
