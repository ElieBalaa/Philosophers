/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: the-flash <the-flash@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 00:00:00 by the-flash         #+#    #+#             */
/*   Updated: 2025/01/04 00:00:00 by the-flash        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				times_eaten;
	long			last_meal_time;
	pid_t			pid;
	pthread_t		monitor_thread;
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
	sem_t			*forks;
	sem_t			*print_sem;
	sem_t			*death_sem;
	sem_t			*meal_sem;
	t_philo			*philos;
	// Track initialization status
	int				forks_initialized;
	int				print_sem_initialized;
	int				death_sem_initialized;
	int				meal_sem_initialized;
	int				philos_allocated;
}	t_data;

/* init_bonus.c */
int		init_data_bonus(t_data *data, int argc, char **argv);
int		init_semaphores(t_data *data);
int		init_philos_bonus(t_data *data);
void	cleanup_data_bonus(t_data *data);

/* utils_bonus.c */
long	get_time_bonus(void);
void	precise_sleep_bonus(long time_ms);
void	safe_print_bonus(t_philo *philo, char *msg);

/* philosopher_bonus.c */
void	philosopher_process(t_philo *philo);
void	eat_bonus(t_philo *philo);
void	think_and_sleep_bonus(t_philo *philo);
void	take_forks_bonus(t_philo *philo);

/* monitor_bonus.c */
void	*monitor_routine_bonus(void *arg);

/* main_bonus.c */
int		main(int argc, char **argv);
int		validate_args_bonus(int argc, char **argv);
long	ft_atol_bonus(char *str);

#endif 