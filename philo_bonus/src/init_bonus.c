/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 12:00:00 by grhaddad          #+#    #+#             */
/*   Updated: 2023/01/01 12:00:00 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

static void	unlink_semaphores(void)
{
	sem_unlink("/philo_forks");
	sem_unlink("/philo_print");
	sem_unlink("/philo_stop");
}

int	init_table(t_table *table, t_params *params)
{
	table->params = *params;
	table->pids = malloc(sizeof(pid_t) * params->n_philo);
	if (!table->pids)
		return (1);
	unlink_semaphores();
	table->forks_sem = sem_open("/philo_forks", O_CREAT, 0644, params->n_philo);
	if (table->forks_sem == SEM_FAILED)
	{
		free(table->pids);
		return (1);
	}
	table->print_sem = sem_open("/philo_print", O_CREAT, 0644, 1);
	if (table->print_sem == SEM_FAILED)
	{
		sem_close(table->forks_sem);
		unlink_semaphores();
		free(table->pids);
		return (1);
	}
	table->stop_sem = sem_open("/philo_stop", O_CREAT, 0644, 0);
	if (table->stop_sem == SEM_FAILED)
	{
		sem_close(table->forks_sem);
		sem_close(table->print_sem);
		unlink_semaphores();
		free(table->pids);
		return (1);
	}
	return (0);
}