/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grhaddad <grhaddad@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 12:00:00 by grhaddad          #+#    #+#             */
/*   Updated: 2023/01/01 12:00:00 by grhaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	run_simulation(t_params *params)
{
	t_shared	shared;
	t_philo		*philos;

	if (init_shared(&shared, params) != 0)
		return (1);
	philos = init_philos(&shared);
	if (!philos)
	{
		cleanup_shared(&shared);
		return (1);
	}
	if (start_simulation(philos, &shared) != 0)
	{
		cleanup_philos(philos, &shared);
		cleanup_shared(&shared);
		return (1);
	}
	cleanup_philos(philos, &shared);
	cleanup_shared(&shared);
	return (0);
}

int	main(int ac, char **av)
{
	t_params	params;

	if (parse_args(ac, av, &params) != 0)
		return (1);
	return (run_simulation(&params));
}
