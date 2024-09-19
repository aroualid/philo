#ifndef PHILO_H
# define PHILO_H

typedef struct s_args t_args;


# include "stdio.h"
# include <limits.h>
# include <stdlib.h>
# include <threads.h>
# include <pthread.h>

typedef struct s_philo
{
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					each_eat;
	int					philo_nb;
	pthread_t			thread;
	pthread_mutex_t		left_fork;
	pthread_mutex_t		right_fork;
	t_args				*args;
}						t_philo;

typedef struct s_args
{
	int					nb_philo;
	pthread_mutex_t		mutex;
	t_philo				**philo;
}						t_args;

long	ft_atol(const char *str);
int		ft_strlen(char *s);
int		ft_isdigit(int c);

#endif
