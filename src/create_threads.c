#include "../philo.h"
#include <pthread.h>

int    check_eat(t_args *args)
{
    int    j;

    j = 0;
    while (j < args->nb_philo)
    {
        if (args->philo[j]->nb_eat < args->philo[j]->each_eat)
        {
            return (0) ;
        }
        j++;
    }
    if (j == args->nb_philo)
    {
        args->all_eat = 1;
        printf("all philosophers have eaten\n");
        pthread_mutex_unlock(&args->mutex);
        return (1);
    }
    return (0);
}

void    check_dead(t_args *args, int i)
{
    args->die = 1;
    printf("%zu %d died\n", what_time(args), i + 1);
    pthread_mutex_unlock(&args->mutex);
    return ;
}

void    monitoring(t_args *args)
{
    int i = 0;
    while (1)
    {
        while (i < args->nb_philo)
        {
            pthread_mutex_lock(&args->mutex);
            if (what_time(args) - args->philo[i]->last_eat > args->philo[i]->time_to_die)
                return check_dead(args, i);
            if (args->philo[i]->each_eat != -1 && check_eat(args) == 1)
                return ;
            pthread_mutex_unlock(&args->mutex);  
            i++;
        }
        usleep(500);
        i = 0;
    }
}


void join_dead(t_args *args)
{
    int j = 0;

    if (args->die == 1 || args->all_eat == 1)
    {
        if (args->nb_philo > 1)
        {
            while (j < args->nb_philo)
            {
                pthread_join(args->philo[j]->thread, NULL);
                j++;
            }
        }
        return ;
    }
}

int    create_threads(t_args *args, void *rou)
{
    int    i;

    i = 0;
    pthread_mutex_init(&args->mutex, NULL);
    while (i < args->nb_philo)
    {
        if (pthread_create(&args->philo[i]->thread ,NULL, rou, args->philo[i])) 
        {
            printf("Erreur lors de la création du thread\n");
            return (1);
        }
        i++;
    }
    i = 0;
    monitoring(args);
    join_dead(args);
    pthread_mutex_destroy(&args->mutex);
    return (0);
}
