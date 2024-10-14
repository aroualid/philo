/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroualid <aroualid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:40:08 by aroualid          #+#    #+#             */
/*   Updated: 2024/10/07 18:40:18 by aroualid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_strlen(char *s)
{
	int	i ;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n > 0)
	{
		*(p++) = 0;
		n--;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;

	if (nmemb == 0 || size == 0)
		return (malloc (0));
	if (SIZE_MAX / nmemb < size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

void	free_philo(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_philo)
	{
		if (args->philo[i])
			free(args->philo[i]);
		i++;
	}
	if (args->forks)
		free (args->forks);
	if (args->philo)
		free (args->philo);
}
