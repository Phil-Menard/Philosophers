/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:01:15 by pmenard           #+#    #+#             */
/*   Updated: 2025/04/22 09:54:08 by pmenard          ###   ########.fr       */
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
	t_time			timer;
	t_time			starve_timer;
	int				*one_died;
	int				*ate_enough;
	int				id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_time_must_eat;
	int				nb_philo;
}	t_philo;

typedef struct s_table
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	death_mutex;
	t_philo			*philosophers;
	int				nb_philo;
	int				enough_meal;
	int				dead;
}	t_table;

int		ft_atoi(const char *nptr);
int		init_philosophers(t_table *table, char **argv);
int		one_philo(t_philo *philo);
void	display_instruction(t_philo *philo, char *str);
void	take_fork(t_philo *philo);
int		check_death(t_philo *philo);
void	go_eat(t_philo *philo);
void	go_sleep(t_philo *philo);
void	go_think(t_philo *philo);
long	calcul_elapsed_time(t_philo *philo);
long	calcul_starving_time(t_philo *philo);
int		monitor_instructions(t_philo *philo, int time_to_wait);
int		count_meals(t_philo *philo);
void	free_some(t_table *table, int i);
void	free_all(t_table *table);

#endif