/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:58:36 by pmenard           #+#    #+#             */
/*   Updated: 2025/02/17 14:35:32 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philosophers(t_table *table)
{
	int	i;

	table->philosophers = malloc(table->nb_philo * sizeof(t_philo));
	table->forks = malloc(table->nb_philo * sizeof(pthread_mutex_t));
	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < table->nb_philo)
	{
		table->philosophers[i].id = i + 1;
		table->philosophers[i].fork_left = &table->forks[i];
		if (i == table->nb_philo - 1)
			table->philosophers[i].fork_right = &table->forks[0];
		else
			table->philosophers[i].fork_right = &table->forks[i + 1];
		i++;
	}
}

void	*handle_threads(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	pthread_mutex_lock(philo->fork_left);
	printf("%d has taken his left fork\n", philo->id);
	pthread_mutex_lock(philo->fork_right);
	printf("%d has taken his right fork\n", philo->id);
	printf("%d is eating\n", philo->id);
	usleep(500);
	printf("%d finished eating\n", philo->id);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	return (NULL);
}

int	start_philosophers(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nb_philo)
	{
		if (pthread_create(&table->philosophers[i].thread, NULL, handle_threads,
				&table->philosophers[i]))
		{
			printf("Erreur lors de la creation du thread.\n");
			free_philo_and_forks(table, i);
			return (1);
		}
	}
	i = -1;
	while (++i < table->nb_philo)
	{
		if (pthread_join(table->philosophers[i].thread, NULL))
		{
			printf("Erreur lors de l'attente du thread.\n");
			free_philo_and_forks(table, i);
			return (1);
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;

	(void) argc;
	table.nb_philo = ft_atoi(argv[1]);
	init_philosophers(&table);
	if (start_philosophers(&table) == 1)
		return (1);
	free_all(&table);
	return (0);
}
