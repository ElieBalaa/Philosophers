/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: the-flash <the-flash@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 00:00:00 by the-flash         #+#    #+#             */
/*   Updated: 2025/01/04 00:00:00 by the-flash        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"

static int	init_fork_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			free(data->forks);
			data->forks = NULL;
			return (0);
		}
		i++;
	}
	data->forks_initialized = 1;
	return (1);
}

static int	init_other_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->print_mutex, NULL))
	{
		cleanup_data(data);
		return (0);
	}
	data->print_mutex_initialized = 1;
	if (pthread_mutex_init(&data->death_mutex, NULL))
	{
		cleanup_data(data);
		return (0);
	}
	data->death_mutex_initialized = 1;
	if (pthread_mutex_init(&data->meal_mutex, NULL))
	{
		cleanup_data(data);
		return (0);
	}
	data->meal_mutex_initialized = 1;
	return (1);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->num_philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		data->must_eat_count = ft_atol(argv[5]);
	else
		data->must_eat_count = -1;
	data->dead = 0;
	data->all_ate = 0;
	data->forks_initialized = 0;
	data->print_mutex_initialized = 0;
	data->death_mutex_initialized = 0;
	data->meal_mutex_initialized = 0;
	data->philos_allocated = 0;
	if (!init_mutexes(data))
		return (0);
	if (!init_philos(data))
		return (0);
	return (1);
}

int	init_mutexes(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (0);
	if (!init_fork_mutexes(data))
		return (0);
	if (!init_other_mutexes(data))
		return (0);
	return (1);
}

int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
	{
		cleanup_data(data);
		return (0);
	}
	data->philos_allocated = 1;
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].times_eaten = 0;
		data->philos[i].last_meal_time = 0;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		data->philos[i].data = data;
		i++;
	}
	return (1);
}
