/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: the-flash <the-flash@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 00:00:00 by the-flash         #+#    #+#             */
/*   Updated: 2025/01/04 00:00:00 by the-flash        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				times_eaten;
	long			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat_count;
	long			start_time;
	int				dead;
	int				all_ate;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	meal_mutex;
	t_philo			*philos;
	// Track initialization status
	int				forks_initialized;
	int				print_mutex_initialized;
	int				death_mutex_initialized;
	int				meal_mutex_initialized;
	int				philos_allocated;
}	t_data;

/* init.c */
int		init_data(t_data *data, int argc, char **argv);
int		init_mutexes(t_data *data);
int		init_philos(t_data *data);
void	cleanup_data(t_data *data);

/* utils.c */
long	get_time(void);
void	precise_sleep(long time_ms);
void	safe_print(t_philo *philo, char *msg);
int		is_dead(t_data *data);

/* philosopher.c */
void	*philosopher_routine(void *arg);
void	eat(t_philo *philo);
void	think_and_sleep(t_philo *philo);
int		take_forks(t_philo *philo);

/* monitor.c */
void	*monitor_routine(void *arg);
int		check_death(t_data *data);
int		check_all_ate(t_data *data);

/* main.c */
int		main(int argc, char **argv);
int		validate_args(int argc, char **argv);
long	ft_atol(char *str);

#endif