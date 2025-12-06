/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 12:00:00 by grhaddad          #+#    #+#             */
/*   Updated: 2023/01/01 12:00:00 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	cleanup_forks(t_shared *shared)
{
	int	i;

	i = 0;
	while (i < shared->n_philo)
	{
		pthread_mutex_destroy(&shared->forks[i]);
		i++;
	}
	free(shared->forks);
}

void	cleanup_shared(t_shared *shared)
{
	pthread_mutex_destroy(&shared->print_mutex);
	pthread_mutex_destroy(&shared->state_mutex);
	cleanup_forks(shared);
}

void	cleanup_philos(t_philo *philos, t_shared *shared)
{
	(void)shared;
	free(philos);
}
