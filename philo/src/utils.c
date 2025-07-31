/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: the-flash <the-flash@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 00:00:00 by the-flash         #+#    #+#             */
/*   Updated: 2025/01/04 00:00:00 by the-flash        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"

long	get_time(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

void	precise_sleep(long time_ms)
{
	long	start;
	long	current;

	start = get_time();
	current = start;
	while (current - start < time_ms)
	{
		usleep(100);
		current = get_time();
	}
}

void	safe_print(t_philo *philo, char *msg)
{
	long	timestamp;

	pthread_mutex_lock(&philo->data->print_mutex);
	if (!is_dead(philo->data))
	{
		timestamp = get_time() - philo->data->start_time;
		printf("%ld %d %s\n", timestamp, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	is_dead(t_data *data)
{
	int	dead_status;

	pthread_mutex_lock(&data->death_mutex);
	dead_status = data->dead;
	pthread_mutex_unlock(&data->death_mutex);
	return (dead_status);
}
