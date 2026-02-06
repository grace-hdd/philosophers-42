/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 12:00:00 by grhaddad          #+#    #+#             */
/*   Updated: 2023/01/01 12:00:00 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_params
{
	int		n_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		meals_required;
	int		has_meals_required;
}	t_params;

typedef struct s_shared
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	state_mutex;
	long			start_time_ms;
	int				n_philo;
	int				stop;
	t_params		params;
}	t_shared;

typedef struct s_philo
{
	int			id;
	int			left_fork;
	int			right_fork;
	long		last_meal_ms;
	int			meals_eaten;
	pthread_t	thread;
	t_shared	*shared;
}	t_philo;

/*
** PARSING
*/
int		parse_args(int ac, char **av, t_params *params);
long	ft_atol(const char *str);
int		ft_isdigit(int c);
int		ft_isspace(int c);

/*
** SIMULATION
*/
int		init_shared(t_shared *shared, t_params *params);
t_philo	*init_philos(t_shared *shared);
int		start_simulation(t_philo *philos, t_shared *shared);
void	*philosopher_routine(void *arg);

/*
** UTILITIES
*/
long	get_time_ms(void);
void	print_status(t_philo *philo, char *status);
void	responsive_sleep(t_shared *shared, long duration_ms);

/*
** CLEANUP
*/
void	cleanup_philos(t_philo *philos, t_shared *shared);
void	cleanup_shared(t_shared *shared);
void	cleanup_forks(t_shared *shared);

#endif