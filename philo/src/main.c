/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroualid <aroualid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:46:04 by aroualid          #+#    #+#             */
/*   Updated: 2024/10/07 16:34:05 by aroualid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <pthread.h>
#include <unistd.h>

int	create_fork(t_args *args)
{
	int				i;

	i = 0;
	args->forks = ft_calloc(sizeof(pthread_mutex_t), args->nb_philo);
	while (i < args->nb_philo)
	{
		if (pthread_mutex_init(&args->forks[i], NULL) == -1)
			return (1);
		i++;
	}
	i = 0;
	while (i < args->nb_philo)
	{
		args->philo[i]->right_fork = &args->forks[i];
		if (i != 0)
			args->philo[i]->left_fork = &args->forks[i -1];
		else if (i == 0)
			args->philo[i]->left_fork = &args->forks[args->nb_philo - 1];
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
		args->philo[i] = ft_calloc(1, sizeof(t_philo));
		if (args->philo[i] == NULL)
		{
			printf("Memory allocation failed for philosopher %d\n", i + 1);
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
	i = 0;
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
		if ((atol >= INT_MAX || atol <= 0) || (ft_strlen(av[i]) >= 11))
			return (0);
		j = 0;
		i++;
	}
	return (1);
}

int	check_arg_ok(t_args args, int ac, char **av)
{
	args.nb_philo = ft_atol(av[1]);
	args.philo = ft_calloc(sizeof(t_philo *), args.nb_philo);
	if (args.philo == NULL)
		return (0);
	fill_value(av, &args, ac);
	create_fork(&args);
	what_first_time(&args);
	create_threads(&args, rou);
	return (1);
}

int	main(int ac, char **av)
{
	t_args			args;
	int				i;

	args = (t_args){0};
	i = 0;
	if (ac == 5 || ac == 6)
	{
		if (check_arg(av, ac) == 1)
		{
			if (check_arg_ok(args, ac, av) == 0)
				return (-1);
		}
		else
			return (printf ("args error\n"), -1);
	}
	else
		printf ("non\n");
}
