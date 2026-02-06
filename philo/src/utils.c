/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 12:00:00 by grhaddad          #+#    #+#             */
/*   Updated: 2023/01/01 12:00:00 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_status(t_philo *philo, char *status)
{
	long	elapsed;

	elapsed = get_time_ms() - philo->shared->start_time_ms;
	pthread_mutex_lock(&philo->shared->state_mutex);
	pthread_mutex_lock(&philo->shared->print_mutex);
	if (!philo->shared->stop)
		printf("%ld %d %s\n", elapsed, philo->id, status);
	pthread_mutex_unlock(&philo->shared->print_mutex);
	pthread_mutex_unlock(&philo->shared->state_mutex);
}

void	responsive_sleep(t_shared *shared, long duration_ms)
{
	long	start;

	start = get_time_ms();
	while (get_time_ms() - start < duration_ms)
	{
		pthread_mutex_lock(&shared->state_mutex);
		if (shared->stop)
		{
			pthread_mutex_unlock(&shared->state_mutex);
			break ;
		}
		pthread_mutex_unlock(&shared->state_mutex);
		usleep(500);
	}
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

long	ft_atol(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}
