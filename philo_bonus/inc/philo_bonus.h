/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 12:00:00 by grhaddad          #+#    #+#             */
/*   Updated: 2023/01/01 12:00:00 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_params
{
	int		n_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		meals_required;
	int		has_meals_required;
}	t_params;

typedef struct s_philo
{
	int			id;
	pid_t		pid;
	long		last_meal_ms;
	int			meals_eaten;
	t_params	*params;
	sem_t		*forks_sem;
	sem_t		*print_sem;
	sem_t		*stop_sem;
	sem_t		*state_sem;
	long		start_time_ms;
}	t_philo;

typedef struct s_table
{
	t_params	params;
	pid_t		*pids;
	sem_t		*forks_sem;
	sem_t		*print_sem;
	sem_t		*stop_sem;
	long		start_time_ms;
}	t_table;

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
int		init_table(t_table *table, t_params *params);
void	start_simulation(t_table *table);
void	philosopher_process(t_table *table, int id);
void	*monitor_routine(void *arg);

/*
** UTILITIES
*/
long	get_time_ms(void);
void	print_status(t_philo *philo, char *status);

/*
** CLEANUP
*/
void	cleanup_table(t_table *table);

#endif