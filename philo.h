/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroualid <aroualid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:37:58 by aroualid          #+#    #+#             */
/*   Updated: 2024/10/14 11:29:11 by aroualid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "stdio.h"
# include <limits.h>
# include <stdlib.h>
# include <threads.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdint.h>

typedef struct s_args	t_args;

typedef struct s_philo
{
	unsigned long		time_to_die;
	unsigned long		time_to_eat;
	unsigned long		time_to_sleep;
	int					each_eat;
	unsigned long		last_eat;
	int					nb_eat;
	int					philo_nb;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_args				*args;
}						t_philo;

typedef struct s_args
{
	int					nb_philo;
	pthread_mutex_t		mutex;
	pthread_mutex_t		*forks;
	int					die;
	int					all_eat;
	unsigned long		first_time;
	t_philo				**philo;
}						t_args;

long				ft_atol(const char *str);
int					ft_strlen(char *s);
int					ft_isdigit(int c);
unsigned long		what_time(t_args *args);
void				what_first_time(t_args *args);
void				my_usleep(unsigned long time, t_args *args);
void				*rou(t_philo *philo);
int					create_threads(t_args *args, void *rou);
void				*ft_calloc(size_t nmemb, size_t size);
void				free_philo(t_args *args);
void				*one_philo(t_philo *philo);
#endif
