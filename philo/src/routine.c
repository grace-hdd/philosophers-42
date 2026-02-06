/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 12:00:00 by grhaddad          #+#    #+#             */
/*   Updated: 2023/01/01 12:00:00 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	grab_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->shared->forks[philo->right_fork]);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->shared->forks[philo->left_fork]);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->shared->forks[philo->left_fork]);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->shared->forks[philo->right_fork]);
		print_status(philo, "has taken a fork");
	}
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->state_mutex);
	philo->last_meal_ms = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->shared->state_mutex);
	print_status(philo, "is eating");
	responsive_sleep(philo->shared, philo->shared->params.time_to_eat);
}

static void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->shared->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->shared->forks[philo->right_fork]);
}

static void	*philo_loop(t_philo *philo)
{
	int	should_stop;

	while (1)
	{
		pthread_mutex_lock(&philo->shared->state_mutex);
		should_stop = philo->shared->stop;
		pthread_mutex_unlock(&philo->shared->state_mutex);
		if (should_stop)
			break ;
		print_status(philo, "is thinking");
		grab_forks(philo);
		eat(philo);
		release_forks(philo);
		print_status(philo, "is sleeping");
		responsive_sleep(philo->shared, philo->shared->params.time_to_sleep);
	}
	return (NULL);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->shared->n_philo == 1)
	{
		print_status(philo, "has taken a fork");
		responsive_sleep(philo->shared, philo->shared->params.time_to_die);
		return (NULL);
	}
	philo_loop(philo);
	return (NULL);
}
