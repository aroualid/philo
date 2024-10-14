/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroualid <aroualid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:28:29 by aroualid          #+#    #+#             */
/*   Updated: 2024/10/14 11:28:52 by aroualid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->args->mutex);
	if (philo->args->die == 0)
		printf("%zu %d has taken a fork\n", what_time(philo->args),
			philo->philo_nb);
	pthread_mutex_unlock(&philo->args->mutex);
	pthread_mutex_unlock(philo->right_fork);
	my_usleep(philo->time_to_die, philo->args);
	return (NULL);
}
