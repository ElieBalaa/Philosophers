/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: the-flash <the-flash@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 00:00:00 by the-flash         #+#    #+#             */
/*   Updated: 2025/01/04 00:00:00 by the-flash        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo_bonus.h"

static void	cleanup_semaphores(t_data *data)
{
	if (data->print_sem && data->print_sem_initialized)
	{
		sem_close(data->print_sem);
		sem_unlink("/print");
		data->print_sem = NULL;
		data->print_sem_initialized = 0;
	}
	if (data->death_sem && data->death_sem_initialized)
	{
		sem_close(data->death_sem);
		sem_unlink("/death");
		data->death_sem = NULL;
		data->death_sem_initialized = 0;
	}
	if (data->meal_sem && data->meal_sem_initialized)
	{
		sem_close(data->meal_sem);
		sem_unlink("/meal");
		data->meal_sem = NULL;
		data->meal_sem_initialized = 0;
	}
}

void	cleanup_data_bonus(t_data *data)
{
	if (data->forks && data->forks_initialized)
	{
		sem_close(data->forks);
		sem_unlink("/forks");
		data->forks = NULL;
		data->forks_initialized = 0;
	}
	cleanup_semaphores(data);
	if (data->philos && data->philos_allocated)
	{
		free(data->philos);
		data->philos = NULL;
		data->philos_allocated = 0;
	}
}
