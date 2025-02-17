/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:01:15 by pmenard           #+#    #+#             */
/*   Updated: 2025/02/17 14:33:46 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	int				id;
}	t_philo;

typedef struct s_table
{
	pthread_mutex_t	*forks;
	t_philo			*philosophers;
	int				nb_philo;
}	t_table;

int		ft_atoi(const char *nptr);
void	free_philo_and_forks(t_table *table, int i);
void	free_all(t_table *table);

#endif