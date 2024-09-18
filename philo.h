#ifndef PHILO_H
# define PHILO_H

# include "stdio.h"
# include <limits.h>
# include <stdlib.h>
# include <threads.h>
# include <pthread.h>

typedef struct s_args
{
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					each_eat;
	int					philo_n;				
	pthread_mutex_t		mutex;

}						t_args;

typedef struct s_philo {
    int philo_n;
    t_args *args;
} t_philo;

long	ft_atol(const char *str);
int		ft_strlen(char *s);
int		ft_isdigit(int c);

#endif
