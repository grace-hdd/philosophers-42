#include "../inc/philo.h"

static int	check_all_fed(t_philo *philos, t_shared *shared)
{
    int	i;

    if (!shared->params.has_meals_required)
        return (0);
    i = 0;
    while (i < shared->n_philo)
    {
        if (philos[i].meals_eaten < shared->params.meals_required)
            return (0);
        i++;
    }
    return (1);
}

static int	check_death(t_philo *philos, t_shared *shared)
{
    long	elapsed;
    int		i;

    i = 0;
    while (i < shared->n_philo)
    {
        pthread_mutex_lock(&shared->state_mutex);
        elapsed = get_time_ms() - philos[i].last_meal_ms;
        if (elapsed > shared->params.time_to_die)
        {
            shared->stop = 1;
            printf("%ld %d died\n", get_time_ms() - shared->start_time_ms,
                philos[i].id);
            pthread_mutex_unlock(&shared->state_mutex);
            return (1);
        }
        pthread_mutex_unlock(&shared->state_mutex);
        i++;
    }
    return (0);
}

void	monitor_philosophers(t_philo *philos, t_shared *shared)
{
    while (1)
    {
        if (check_death(philos, shared))
            return ;
        pthread_mutex_lock(&shared->state_mutex);
        if (check_all_fed(philos, shared))
        {
            shared->stop = 1;
            pthread_mutex_unlock(&shared->state_mutex);
            return ;
        }
        pthread_mutex_unlock(&shared->state_mutex);
        usleep(100);
    }
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
	monitor_philosophers(philos, shared);
	i = 0;
	while (i < shared->n_philo)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	return (0);
}
