/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:53:51 by pmenard           #+#    #+#             */
/*   Updated: 2025/05/06 13:23:41 by pmenard          ###   ########.fr       */
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
		table->philosophers[i].check_fork_left = &table->check_fork[0];
		table->philosophers[i].check_fork_right = &table->check_fork[0];
	}
	else
	{
		table->philosophers[i].fork_left = &table->forks[i];
		table->philosophers[i].check_fork_left = &table->check_fork[i];
		if (i == table->nb_philo - 1)
		{
			table->philosophers[i].fork_right = &table->forks[0];
			table->philosophers[i].check_fork_right = &table->check_fork[0];
		}
		else
		{
			table->philosophers[i].fork_right = &table->forks[i + 1];
			table->philosophers[i].check_fork_right = &table->check_fork[i + 1];
		}
	}
}

void	init_mutexes(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nb_philo)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		table->check_fork[i] = 0;
	}
	pthread_mutex_init(&table->print, NULL);
	pthread_mutex_init(&table->death_mutex, NULL);
	pthread_mutex_init(&table->ready_mutex, NULL);
	pthread_mutex_init(&table->meal_mutex, NULL);
	pthread_mutex_init(&table->time_mutex, NULL);
	pthread_mutex_init(&table->check_fork_mutex, NULL);
}

int	init_philosophers(t_table *table, char **argv)
{
	int	i;

	table->philosophers = malloc(table->nb_philo * sizeof(t_philo));
	table->forks = malloc(table->nb_philo * sizeof(pthread_mutex_t));
	table->check_fork = malloc(table->nb_philo * sizeof(int));
	table->enough_meal = 0;
	table->all_ready = 0;
	init_mutexes(table);
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
		table->philosophers[i].timer = &table->global_timer;
		table->philosophers[i].ready = &table->all_ready;
		table->philosophers[i].ready_mutex = &table->ready_mutex;
		table->philosophers[i].time_mutex = &table->time_mutex;
		table->philosophers[i].check_fork_mutex = &table->check_fork_mutex;
	}
	return (0);
}

//wait for all threads to be created
void	wait_threads(t_philo *philo)
{
	pthread_mutex_lock(philo->ready_mutex);
	*philo->ready += 1;
	pthread_mutex_unlock(philo->ready_mutex);
	while (1)
	{
		pthread_mutex_lock(philo->ready_mutex);
		if (*philo->ready == philo->nb_philo)
		{
			pthread_mutex_unlock(philo->ready_mutex);
			break ;
		}
		else
			pthread_mutex_unlock(philo->ready_mutex);
		usleep(50);
	}
}
