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
		precise_sleep(philo->data->time_to_die);
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
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	think_and_sleep(t_philo *philo)
{
	safe_print(philo, "is sleeping");
	precise_sleep(philo->data->time_to_sleep);
	safe_print(philo, "is thinking");
	usleep(1000);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(100);
	while (!is_dead(philo->data))
	{
		if (!take_forks(philo))
			break ;
		eat(philo);
		think_and_sleep(philo);
	}
	return (NULL);
}
