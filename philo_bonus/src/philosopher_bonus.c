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
	sem_wait(philo->data->meal_sem);
	philo->last_meal_time = get_time_bonus();
	philo->times_eaten++;
	sem_post(philo->data->meal_sem);
	precise_sleep_bonus(philo->data->time_to_eat);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	think_and_sleep_bonus(t_philo *philo)
{
	int	adaptive_delay;
	int	fairness_delay;
	int	total_cycle_time;

	safe_print_bonus(philo, "is sleeping");
	precise_sleep_bonus(philo->data->time_to_sleep);
	safe_print_bonus(philo, "is thinking");
	adaptive_delay = 1000;
	if (philo->data->num_philos > 100)
		adaptive_delay = 2000;
	else if (philo->data->num_philos > 50)
		adaptive_delay = 1500;
	total_cycle_time = philo->data->time_to_eat + philo->data->time_to_sleep;
	fairness_delay = 0;
	if (philo->data->time_to_die <= 200)
		fairness_delay = 0;
	else if (total_cycle_time * 10 >= philo->data->time_to_die * 9)
		fairness_delay = philo->data->time_to_die / 3;
	else if (total_cycle_time * 10 >= philo->data->time_to_die * 4)
		fairness_delay = philo->data->time_to_die / 8;
	else if (philo->data->time_to_die <= 500)
		fairness_delay = philo->data->time_to_die / 15;
	else if (philo->data->time_to_die <= 1000)
		fairness_delay = philo->data->time_to_die / 50;
	usleep(adaptive_delay + fairness_delay);
}

void	philosopher_process(t_philo *philo)
{
	int	stagger_delay;

	if (pthread_create(&philo->monitor_thread, NULL,
			monitor_routine_bonus, philo))
		exit(1);
	pthread_detach(philo->monitor_thread);
	if (philo->data->num_philos == 1)
	{
		sem_wait(philo->data->forks);
		safe_print_bonus(philo, "has taken a fork");
		sem_post(philo->data->forks);
		while (1)
			usleep(1000);
	}
	stagger_delay = (philo->id % 2) * 1000;
	if (philo->data->time_to_die <= 200)
	{
		if (philo->data->num_philos >= 16)
			stagger_delay = (philo->id % 16) * 100;
		else if (philo->data->num_philos >= 8)
			stagger_delay = (philo->id % 4) * 1000;
		else
			stagger_delay = (philo->id % 3) * 2000;
	}
	if (philo->data->time_to_die <= 1000)
		usleep(stagger_delay);
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
