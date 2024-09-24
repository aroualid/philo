#ifndef PHILO_H
# define PHILO_H

typedef struct s_args t_args;


# include "stdio.h"
# include <limits.h>
# include <stdlib.h>
# include <threads.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	unsigned long		time_to_die;
	unsigned long		time_to_eat;
	unsigned long		time_to_sleep;
	unsigned long		each_eat;
	unsigned long		last_eat;
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
	int					die;
	unsigned long		first_time;
	t_philo				**philo;
}						t_args;

long	ft_atol(const char *str);
int		ft_strlen(char *s);
int		ft_isdigit(int c);
unsigned long		what_time(t_args *args);
void		what_first_time(t_args *args);
void	my_usleep(unsigned long time, t_args *args);

#endif
