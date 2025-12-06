/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 12:00:00 by grhaddad          #+#    #+#             */
/*   Updated: 2023/01/01 12:00:00 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

static void	wait_and_terminate(t_table *table)
{
	int	i;

	sem_wait(table->stop_sem);
	i = 0;
	while (i < table->params.n_philo)
	{
		kill(table->pids[i], SIGKILL);
		i++;
	}
}

void	start_simulation(t_table *table)
{
	int		i;
	pid_t	pid;

	i = 0;
	table->start_time_ms = get_time_ms();
	while (i < table->params.n_philo)
	{
		pid = fork();
		if (pid == -1)
		{
			while (--i >= 0)
				kill(table->pids[i], SIGKILL);
			return ;
		}
		if (pid == 0)
		{
			philosopher_process(table, i + 1);
			exit(0);
		}
		table->pids[i] = pid;
		i++;
	}
	wait_and_terminate(table);
}

int	main(int ac, char **av)
{
	t_params	params;
	t_table		table;

	if (parse_args(ac, av, &params) != 0)
		return (1);
	if (init_table(&table, &params) != 0)
	{
		printf("Error: Failed to initialize table\n");
		return (1);
	}
	start_simulation(&table);
	cleanup_table(&table);
	return (0);
}