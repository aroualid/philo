#include "../philo.h"
#include <strings.h>

int	check_arg(char **av, int ac)
{
	int	i;
	int	atol;
	t_args args;

	bzero(&args, sizeof(t_args));
	atol = 0;
	i = 1;
	while (av[i] && i <= ac)
	{
		atol = ft_atol(av[i]);
		if ((atol > INT_MAX || atol < INT_MIN) || (ft_strlen(av[i]) >= 11))
			return (0);

			
	}
}

int main (int ac, char **av)
{
	if (ac == 5 || ac == 6)
		printf ("ok\n");
	else
		printf ("non\n");
	(void) av;
}
