#include "../philo.h"

void	what_first_time(t_args *args)
{
    struct timeval	tv;

	gettimeofday(&tv, NULL);
    args->first_time =  tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

void	what_time(t_args *args)
{
    struct timeval	tv;
	gettimeofday(&tv, NULL);
	args->time = (tv.tv_sec * 1000 + tv.tv_usec / 1000) - args->first_time;

}

void	my_usleep(unsigned long time, t_args *args)
{
	unsigned long	time_to_wait;
	unsigned long	first_time;
	
	first_time = args->time;
	time_to_wait = first_time + time;;

	while (args->time < time_to_wait)
	{
		usleep (20);
		what_time(args);
	}
}
