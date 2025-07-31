/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: the-flash <the-flash@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 00:00:00 by the-flash         #+#    #+#             */
/*   Updated: 2025/01/04 00:00:00 by the-flash        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"

static int	check_philosopher_death(t_data *data, int i)
{
	long	current_time;
	long	last_meal;

	current_time = get_time();
	pthread_mutex_lock(&data->meal_mutex);
	last_meal = data->philos[i].last_meal_time;
	pthread_mutex_unlock(&data->meal_mutex);
	if (current_time - last_meal >= data->time_to_die)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (!data->dead)
		{
			data->dead = 1;
			pthread_mutex_unlock(&data->death_mutex);
			pthread_mutex_lock(&data->print_mutex);
			printf("%ld %d died\n", current_time - data->start_time,
				data->philos[i].id);
			pthread_mutex_unlock(&data->print_mutex);
			return (1);
		}
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	return (0);
}

int	check_death(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (check_philosopher_death(data, i))
			return (1);
		i++;
	}
	return (0);
}

int	check_all_ate(t_data *data)
{
	int	i;
	int	all_ate;

	if (data->must_eat_count == -1)
		return (0);
	i = 0;
	all_ate = 1;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->meal_mutex);
		if (data->philos[i].times_eaten < data->must_eat_count)
			all_ate = 0;
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	if (all_ate)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (!data->dead)
			data->dead = 1;
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!is_dead(data))
	{
		if (check_death(data) || check_all_ate(data))
			break ;
		usleep(50);
	}
	return (NULL);
}
