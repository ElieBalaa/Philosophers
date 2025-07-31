/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: the-flash <the-flash@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 00:00:00 by the-flash         #+#    #+#             */
/*   Updated: 2025/01/04 00:00:00 by the-flash        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo_bonus.h"

void	*monitor_routine_bonus(void *arg)
{
	t_philo	*philo;
	long	current_time;
	long	last_meal;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->data->meal_sem);
		current_time = get_time_bonus();
		last_meal = philo->last_meal_time;
		sem_post(philo->data->meal_sem);
		if (current_time - last_meal >= philo->data->time_to_die)
		{
			sem_wait(philo->data->print_sem);
			printf("%ld %d died\n", current_time - philo->data->start_time,
				philo->id);
			exit(1);
		}
		usleep(50);
	}
	return (NULL);
}
