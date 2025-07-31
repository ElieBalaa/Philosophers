/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: the-flash <the-flash@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 00:00:00 by the-flash         #+#    #+#             */
/*   Updated: 2025/01/04 00:00:00 by the-flash        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"

static void	cleanup_mutexes(t_data *data)
{
	if (data->print_mutex_initialized)
	{
		pthread_mutex_destroy(&data->print_mutex);
		data->print_mutex_initialized = 0;
	}
	if (data->death_mutex_initialized)
	{
		pthread_mutex_destroy(&data->death_mutex);
		data->death_mutex_initialized = 0;
	}
	if (data->meal_mutex_initialized)
	{
		pthread_mutex_destroy(&data->meal_mutex);
		data->meal_mutex_initialized = 0;
	}
}

void	cleanup_data(t_data *data)
{
	int	i;

	if (data->forks && data->forks_initialized)
	{
		i = 0;
		while (i < data->num_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
		data->forks = NULL;
		data->forks_initialized = 0;
	}
	cleanup_mutexes(data);
	if (data->philos && data->philos_allocated)
	{
		free(data->philos);
		data->philos = NULL;
		data->philos_allocated = 0;
	}
}
