/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: the-flash <the-flash@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 00:00:00 by the-flash         #+#    #+#             */
/*   Updated: 2025/01/04 00:00:00 by the-flash        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo_bonus.h"

long	ft_atol_bonus(char *str)
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

int	validate_args_bonus(int argc, char **argv)
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
		if (ft_atol_bonus(argv[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}

int	start_simulation_bonus(t_data *data)
{
	int	i;
	int	status;

	data->start_time = get_time_bonus();
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].pid = fork();
		if (data->philos[i].pid == 0)
			philosopher_process(&data->philos[i]);
		i++;
	}
	waitpid(-1, &status, 0);
	i = 0;
	while (i < data->num_philos)
	{
		kill(data->philos[i].pid, SIGKILL);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!validate_args_bonus(argc, argv))
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	memset(&data, 0, sizeof(t_data));
	if (!init_data_bonus(&data, argc, argv))
	{
		printf("Error: Initialization failed\n");
		cleanup_data_bonus(&data);
		return (1);
	}
	if (!start_simulation_bonus(&data))
	{
		printf("Error: Simulation failed\n");
		cleanup_data_bonus(&data);
		return (1);
	}
	cleanup_data_bonus(&data);
	return (0);
}
