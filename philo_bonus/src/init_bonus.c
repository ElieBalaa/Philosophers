/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: the-flash <the-flash@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 00:00:00 by the-flash         #+#    #+#             */
/*   Updated: 2025/01/04 00:00:00 by the-flash        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo_bonus.h"

static int	init_other_semaphores(t_data *data)
{
	data->print_sem = sem_open("/print", O_CREAT, 0644, 1);
	if (data->print_sem == SEM_FAILED)
	{
		cleanup_data_bonus(data);
		return (0);
	}
	data->print_sem_initialized = 1;
	data->death_sem = sem_open("/death", O_CREAT, 0644, 1);
	if (data->death_sem == SEM_FAILED)
	{
		cleanup_data_bonus(data);
		return (0);
	}
	data->death_sem_initialized = 1;
	data->meal_sem = sem_open("/meal", O_CREAT, 0644, 1);
	if (data->meal_sem == SEM_FAILED)
	{
		cleanup_data_bonus(data);
		return (0);
	}
	data->meal_sem_initialized = 1;
	return (1);
}

int	init_data_bonus(t_data *data, int argc, char **argv)
{
	data->num_philos = ft_atol_bonus(argv[1]);
	data->time_to_die = ft_atol_bonus(argv[2]);
	data->time_to_eat = ft_atol_bonus(argv[3]);
	data->time_to_sleep = ft_atol_bonus(argv[4]);
	if (argc == 6)
		data->must_eat_count = ft_atol_bonus(argv[5]);
	else
		data->must_eat_count = -1;
	data->forks_initialized = 0;
	data->print_sem_initialized = 0;
	data->death_sem_initialized = 0;
	data->meal_sem_initialized = 0;
	data->philos_allocated = 0;
	if (!init_semaphores(data))
		return (0);
	if (!init_philos_bonus(data))
		return (0);
	return (1);
}

int	init_semaphores(t_data *data)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/death");
	sem_unlink("/meal");
	data->forks = sem_open("/forks", O_CREAT, 0644, data->num_philos);
	if (data->forks == SEM_FAILED)
		return (0);
	data->forks_initialized = 1;
	if (!init_other_semaphores(data))
		return (0);
	return (1);
}

int	init_philos_bonus(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
	{
		cleanup_data_bonus(data);
		return (0);
	}
	data->philos_allocated = 1;
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].times_eaten = 0;
		data->philos[i].last_meal_time = 0;
		data->philos[i].pid = 0;
		data->philos[i].data = data;
		i++;
	}
	return (1);
}
