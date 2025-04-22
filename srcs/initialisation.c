/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:53:51 by pmenard           #+#    #+#             */
/*   Updated: 2025/04/22 17:26:17 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//init values for philosophers
int	init_values(t_philo *philosopher, char **argv)
{
	philosopher->time_to_die = ft_atoi(argv[2]);
	philosopher->time_to_eat = ft_atoi(argv[3]);
	philosopher->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philosopher->nb_time_must_eat = ft_atoi(argv[5]);
	else
		philosopher->nb_time_must_eat = -1;
	return (0);
}

void	check_nb_philo(t_table *table, int i)
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

int	init_philosophers(t_table *table, char **argv)
{
	int	i;

	table->philosophers = malloc(table->nb_philo * sizeof(t_philo));
	table->forks = malloc(table->nb_philo * sizeof(pthread_mutex_t));
	table->enough_meal = 0;
	i = -1;
	while (++i < table->nb_philo)
		pthread_mutex_init(&table->forks[i], NULL);
	pthread_mutex_init(&table->print, NULL);
	pthread_mutex_init(&table->death_mutex, NULL);
	pthread_mutex_init(&table->meal_mutex, NULL);
	i = -1;
	while (++i < table->nb_philo)
	{
		table->philosophers[i].id = i + 1;
		table->philosophers[i].death_mutex = &table->death_mutex;
		check_nb_philo(table, i);
		table->philosophers[i].print_mutex = &table->print;
		init_values(&table->philosophers[i], argv);
		table->philosophers[i].one_died = &table->dead;
		table->philosophers[i].ate_enough = &table->enough_meal;
		table->philosophers[i].meal_mutex = &table->meal_mutex;
		table->philosophers[i].nb_philo = table->nb_philo;
	}
	return (0);
}
