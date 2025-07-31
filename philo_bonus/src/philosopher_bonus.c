/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: the-flash <the-flash@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 00:00:00 by the-flash         #+#    #+#             */
/*   Updated: 2025/01/04 00:00:00 by the-flash        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo_bonus.h"

void	take_forks_bonus(t_philo *philo)
{
	sem_wait(philo->data->forks);
	safe_print_bonus(philo, "has taken a fork");
	sem_wait(philo->data->forks);
	safe_print_bonus(philo, "has taken a fork");
}

void	eat_bonus(t_philo *philo)
{
	safe_print_bonus(philo, "is eating");
	sem_wait(philo->data->death_sem);
	sem_wait(philo->data->meal_sem);
	philo->last_meal_time = get_time_bonus();
	philo->times_eaten++;
	sem_post(philo->data->meal_sem);
	sem_post(philo->data->death_sem);
	precise_sleep_bonus(philo->data->time_to_eat);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	think_and_sleep_bonus(t_philo *philo)
{
	safe_print_bonus(philo, "is sleeping");
	precise_sleep_bonus(philo->data->time_to_sleep);
	safe_print_bonus(philo, "is thinking");
	usleep(1000);
}

void	philosopher_process(t_philo *philo)
{
	if (pthread_create(&philo->monitor_thread, NULL,
			monitor_routine_bonus, philo))
		exit(1);
	pthread_detach(philo->monitor_thread);
	while (1)
	{
		take_forks_bonus(philo);
		eat_bonus(philo);
		if (philo->data->must_eat_count != -1
			&& philo->times_eaten >= philo->data->must_eat_count)
			exit(0);
		think_and_sleep_bonus(philo);
	}
}
