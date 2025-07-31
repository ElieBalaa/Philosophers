/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: the-flash <the-flash@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 00:00:00 by the-flash         #+#    #+#             */
/*   Updated: 2025/01/04 00:00:00 by the-flash        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

long	get_time_bonus(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

void	precise_sleep_bonus(long time_ms)
{
	long	start;
	long	current;

	start = get_time_bonus();
	current = start;
	while (current - start < time_ms)
	{
		usleep(100);
		current = get_time_bonus();
	}
}

void	safe_print_bonus(t_philo *philo, char *msg)
{
	long	timestamp;

	sem_wait(philo->data->print_sem);
	timestamp = get_time_bonus() - philo->data->start_time;
	printf("%ld %d %s\n", timestamp, philo->id, msg);
	sem_post(philo->data->print_sem);
} 
