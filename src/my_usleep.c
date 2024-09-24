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
	unsigned long what_is_time;

	first_time = args->time;
	time_to_wait = first_time + time;;
	

	pthread_mutex_lock(&args->mutex);
	what_is_time = args->time;
	pthread_mutex_unlock(&args->mutex);
	while (what_is_time < time_to_wait)
	{
		if (args->die == 1)
			return ;
		usleep (20);
		pthread_mutex_lock(&args->mutex);
		what_time(args);
		what_is_time = args->time;
		pthread_mutex_unlock(&args->mutex);

	}
}
