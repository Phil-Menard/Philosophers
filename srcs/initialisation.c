/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:53:51 by pmenard           #+#    #+#             */
/*   Updated: 2025/04/21 15:33:11 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//init values for philosophers
int	init_values(t_philo *philosopher, char **argv)
{
	if (philosopher->id % 2 == 0)
	{
		philosopher->has_eaten = 0;
		philosopher->has_slept = 0;
		philosopher->has_thought = 1;
	}
	else
	{
		philosopher->has_eaten = 1;
		philosopher->has_slept = 0;
		philosopher->has_thought = 0;
	}
	philosopher->is_dead = 0;
	philosopher->time_to_die = atoi(argv[2]);
	philosopher->time_to_eat = atoi(argv[3]);
	philosopher->time_to_sleep = atoi(argv[4]);
	if (argv[5])
		philosopher->nb_time_must_eat = atoi(argv[5]);
	else
		philosopher->nb_time_must_eat = -1;
	return (0);
}

int	init_philosophers(t_table *table, char **argv)
{
	int	i;

	table->philosophers = malloc(table->nb_philo * sizeof(t_philo));
	table->forks = malloc(table->nb_philo * sizeof(pthread_mutex_t));
	i = -1;
	while (++i < table->nb_philo)
		pthread_mutex_init(&table->forks[i], NULL);
	pthread_mutex_init(&table->print, NULL);
	pthread_mutex_init(&table->death_mutex, NULL);
	i = -1;
	while (++i < table->nb_philo)
	{
		table->philosophers[i].id = i + 1;
		table->philosophers[i].death_mutex = &table->death_mutex;
		if (table->nb_philo == 1)
		{
			table->philosophers[i].fork_left = &table->forks[0];
			table->philosophers[i].fork_right = &table->forks[0];
		}
		else
		{
			table->philosophers[i].fork_left = &table->forks[i];
			if (i == table->nb_philo - 1)
				table->philosophers[i].fork_right = &table->forks[0];
			else
				table->philosophers[i].fork_right = &table->forks[i + 1];
		}
		table->philosophers[i].print_mutex = &table->print;
		init_values(&table->philosophers[i], argv);
		table->philosophers[i].one_died = &table->dead;
	}
	return (0);
}
