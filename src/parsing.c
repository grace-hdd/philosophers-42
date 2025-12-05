#include "../inc/philo.h"

static int	ft_isdigit(int c)
{
    return (c >= '0' && c <= '9');
}

static int	ft_isspace(int c)
{
    return (c == ' ' || c == '\t' || c == '\n'
        || c == '\v' || c == '\f' || c == '\r');
}

static long	ft_atol(const char *str)
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

int	parse_args(int ac, char **av, t_params *params)
{
    long	n_philo_temp;
    long	meals_temp;

    if (ac != 5 && ac != 6)
    {
        printf("Error\n");
        return (1);
    }
    n_philo_temp = ft_atol(av[1]);
    params->time_to_die = ft_atol(av[2]);
    params->time_to_eat = ft_atol(av[3]);
    params->time_to_sleep = ft_atol(av[4]);
    if (n_philo_temp <= 0 || n_philo_temp > 2147483647)
    {
        printf("Error\n");
        return (1);
    }
    if (params->time_to_die <= 0 || params->time_to_die > 2147483647)
    {
        printf("Error\n");
        return (1);
    }
    if (params->time_to_eat <= 0 || params->time_to_eat > 2147483647)
    {
        printf("Error\n");
        return (1);
    }
    if (params->time_to_sleep <= 0 || params->time_to_sleep > 2147483647)
    {
        printf("Error\n");
        return (1);
    }
    params->n_philo = (int)n_philo_temp;
    if (ac == 6)
    {
        meals_temp = ft_atol(av[5]);
        if (meals_temp <= 0 || meals_temp > 2147483647)
        {
            printf("Error\n");
            return (1);
        }
        params->meals_required = (int)meals_temp;
        params->has_meals_required = 1;
    }
    else
        params->has_meals_required = 0;
    return (0);
}
