/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: the-flash <the-flash@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 00:00:00 by the-flash         #+#    #+#             */
/*   Updated: 2025/01/04 00:00:00 by the-flash        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	ft_atol(char *str)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

int	validate_args(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc != 5 && argc != 6)
		return (0);
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		if (ft_atol(argv[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}

int	start_simulation(t_data *data)
{
	pthread_t	monitor;
	int			i;

	data->start_time = get_time();
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].last_meal_time = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL,
				philosopher_routine, &data->philos[i]))
			return (0);
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, data))
		return (0);
	pthread_join(monitor, NULL);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!validate_args(argc, argv))
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	memset(&data, 0, sizeof(t_data));
	if (!init_data(&data, argc, argv))
	{
		printf("Error: Initialization failed\n");
		cleanup_data(&data);
		return (1);
	}
	if (!start_simulation(&data))
	{
		printf("Error: Simulation failed\n");
		cleanup_data(&data);
		return (1);
	}
	cleanup_data(&data);
	return (0);
}
