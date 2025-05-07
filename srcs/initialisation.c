/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:53:51 by pmenard           #+#    #+#             */
/*   Updated: 2025/05/07 10:37:01 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//init values for philosophers
int	init_values(t_philo *philosopher, char **argv)
{
	philosopher->time_to_die = ft_atoi(argv[2]);
	philosopher->time_to_eat = ft_atoi(argv[3]);
	philosopher->time_to_sleep = ft_atoi(argv[4]);
	philosopher->last_meal = get_current_time();
	philosopher->nb_meal = 0;
	return (0);
}

void	assign_forks(t_table *table, int i)
{
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
}

void	init_mutexes(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nb_philo)
		pthread_mutex_init(&table->forks[i], NULL);
	pthread_mutex_init(&table->print, NULL);
	pthread_mutex_init(&table->death_mutex, NULL);
	pthread_mutex_init(&table->meal_mutex, NULL);
}

void	set_timer_start(t_table *table)
{
	int	i;

	i = 0;
	table->start_timer = get_current_time();
	while (i < table->nb_philo)
	{
		table->philosophers[i].start_timer = table->start_timer;
		i++;
	}
}

int	init_philosophers(t_table *table, char **argv)
{
	int	i;

	table->philosophers = malloc(table->nb_philo * sizeof(t_philo));
	table->forks = malloc(table->nb_philo * sizeof(pthread_mutex_t));
	if (argv[5])
		table->required_meal = ft_atoi(argv[5]);
	else
		table->required_meal = -1;
	init_mutexes(table);
	i = -1;
	while (++i < table->nb_philo)
	{
		assign_forks(table, i);
		init_values(&table->philosophers[i], argv);
		table->philosophers[i].id = i + 1;
		table->philosophers[i].death_mutex = &table->death_mutex;
		table->philosophers[i].print_mutex = &table->print;
		table->philosophers[i].meal_mutex = &table->meal_mutex;
		table->philosophers[i].dead = &table->dead;
		table->philosophers[i].nb_philo = table->nb_philo;
		table->philosophers[i].start_timer = table->start_timer;
	}
	return (0);
}
