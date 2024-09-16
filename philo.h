#ifndef PHILO_H
# define PHILO_H

# include "stdio.h"
# include <limits.h>
# include <stdlib.h>

typedef struct s_args
{
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					each_eat;
}						t_args;

long	ft_atol(const char *str);
int		ft_strlen(char *s);
int		ft_isdigit(int c);

#endif
