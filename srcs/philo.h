/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:01:15 by pmenard           #+#    #+#             */
/*   Updated: 2025/04/21 15:32:56 by pmenard          ###   ########.fr       */
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
	int				has_eaten;
	int				has_slept;
	int				has_thought;
	int				is_dead;
	int				*one_died;
	int				id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_time_must_eat;
}	t_philo;

typedef struct s_table
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	death_mutex;
	t_philo			*philosophers;
	int				nb_philo;
	int				dead;
}	t_table;

int		ft_atoi(const char *nptr);
int		init_philosophers(t_table *table, char **argv);
int		go_eat(t_philo *philo);
int		go_sleep(t_philo *philo);
int		go_think(t_philo *philo);
int		check_death(t_philo *philo);
void	free_some(t_table *table, int i);
void	free_all(t_table *table);
long	calcul_elapsed_time(t_philo *philo);
long	calcul_starving_time(t_philo *philo);
int		one_philo(t_philo *philo);

#endif