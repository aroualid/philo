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

	atol = 0;
	i = 1;
	while (av[i] && i <= ac)
	{
		atol = ft_atol(av[i]);
		if ((atol > INT_MAX || atol <= 0) || (ft_strlen(av[i]) >= 11))
			return (0);
		else
			fill_value (i, atol, args);
		i++;
	}
	return (1);
}

int main (int ac, char **av)
{
	t_args *args;

	args = calloc(sizeof(t_args), 1);
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
			printf("nb = %i\n", args->nb_philo);
			printf("nb = %i\n", args->time_to_die);
			printf("nb = %i\n", args->time_to_eat);
			printf("nb = %i\n", args->time_to_sleep);
			printf("nb = %i\n", args->each_eat);
		}
	}
	else
		printf ("non\n");
	free (args);
}
