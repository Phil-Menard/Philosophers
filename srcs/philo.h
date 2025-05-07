/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:01:15 by pmenard           #+#    #+#             */
/*   Updated: 2025/05/07 10:51:49 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_time
{
	struct timeval	start_time;
	struct timeval	end_time;
	long			elapsed_ms;
}	t_time;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*death_mutex;
	pthread_mutex_t	*meal_mutex;
	int				*dead;
	int				id;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meal;
	long			last_meal;
	long			start_timer;
}	t_philo;

typedef struct s_table
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	meal_mutex;
	t_time			global_timer;
	t_philo			*philosophers;
	long			start_timer;
	int				dead;
	int				nb_philo;
	int				required_meal;
}	t_table;

int		ft_atoi(const char *nptr);
int		init_philosophers(t_table *table, char **argv);
void	set_timer_start(t_table *table);
void	*handle_threads(void *arg);
void	display_instruction(t_philo *philo, char *str);
void	monitor_instructions(int time_to_wait);
int		take_fork(t_philo *philo);
int		check_if_dead(t_philo *philo);
void	omg_one_died(t_philo *philo);
void	enough_meals(t_table *table);
long	get_current_time(void);
void	free_all(t_table *table);

#endif