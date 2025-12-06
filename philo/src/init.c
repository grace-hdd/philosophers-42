/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 12:00:00 by grhaddad          #+#    #+#             */
/*   Updated: 2023/01/01 12:00:00 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

static int	init_forks(t_shared *shared, int n_philo)
{
	int	i;

	shared->forks = malloc(sizeof(pthread_mutex_t) * n_philo);
	if (!shared->forks)
		return (1);
	i = 0;
	while (i < n_philo)
	{
		if (pthread_mutex_init(&shared->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&shared->forks[i]);
			free(shared->forks);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_shared(t_shared *shared, t_params *params)
{
	shared->params = *params;
	shared->n_philo = params->n_philo;
	shared->stop = 0;
	shared->start_time_ms = get_time_ms();
	if (init_forks(shared, params->n_philo) != 0)
		return (1);
	if (pthread_mutex_init(&shared->print_mutex, NULL) != 0)
	{
		cleanup_forks(shared);
		return (1);
	}
	if (pthread_mutex_init(&shared->state_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&shared->print_mutex);
		cleanup_forks(shared);
		return (1);
	}
	return (0);
}

t_philo	*init_philos(t_shared *shared)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * shared->n_philo);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < shared->n_philo)
	{
		philos[i].id = i + 1;
		philos[i].left_fork = i;
		philos[i].right_fork = (i + 1) % shared->n_philo;
		philos[i].last_meal_ms = shared->start_time_ms;
		philos[i].meals_eaten = 0;
		philos[i].shared = shared;
		i++;
	}
	return (philos);
}
