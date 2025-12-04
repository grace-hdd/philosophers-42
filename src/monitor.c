#include "../inc/philo.h"

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	int		should_stop;

	philo = (t_philo *)arg;
	if (philo->shared->n_philo == 1)
	{
		print_status(philo, "has taken a fork");
		usleep(philo->shared->params.time_to_die * 1000);
		return (NULL);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->shared->state_mutex);
		should_stop = philo->shared->stop;
		pthread_mutex_unlock(&philo->shared->state_mutex);
		if (should_stop)
			break ;
	}
	return (NULL);
}

int	start_simulation(t_philo *philos, t_shared *shared)
{
	int	i;

	i = 0;
	while (i < shared->n_philo)
	{
		if (pthread_create(&philos[i].thread, NULL,
				philosopher_routine, &philos[i]) != 0)
		{
			shared->stop = 1;
			while (--i >= 0)
				pthread_join(philos[i].thread, NULL);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < shared->n_philo)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	return (0);
}