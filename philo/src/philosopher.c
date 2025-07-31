/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: the-flash <the-flash@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 00:00:00 by the-flash         #+#    #+#             */
/*   Updated: 2025/01/04 00:00:00 by the-flash        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philo->data->num_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		safe_print(philo, "has taken a fork");
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	if (philo->left_fork < philo->right_fork)
		first = philo->left_fork;
	else
		first = philo->right_fork;
	if (first == philo->left_fork)
		second = philo->right_fork;
	else
		second = philo->left_fork;
	pthread_mutex_lock(first);
	safe_print(philo, "has taken a fork");
	pthread_mutex_lock(second);
	safe_print(philo, "has taken a fork");
	return (1);
}

void	eat(t_philo *philo)
{
	safe_print(philo, "is eating");
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = get_time();
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	precise_sleep(philo->data->time_to_eat);
	if (philo->left_fork < philo->right_fork)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

void	think_and_sleep(t_philo *philo)
{
	int	adaptive_delay;
	int	fairness_delay;
	int	total_cycle_time;

	safe_print(philo, "is sleeping");
	precise_sleep(philo->data->time_to_sleep);
	safe_print(philo, "is thinking");
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

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	int		stagger_delay;

	philo = (t_philo *)arg;
	if (philo->data->num_philos == 1)
	{
		take_forks(philo);
		while (!is_dead(philo->data))
			usleep(1000);
		return (NULL);
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
	while (!is_dead(philo->data))
	{
		if (!take_forks(philo))
		{
			usleep(1000);
			break ;
		}
		eat(philo);
		if (is_dead(philo->data))
			break ;
		think_and_sleep(philo);
	}
	return (NULL);
}
