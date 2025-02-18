/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:53:51 by pmenard           #+#    #+#             */
/*   Updated: 2025/02/18 13:15:01 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_values(t_philo *philosopher)
{
	if (philosopher->id % 2 == 0)
	{
		philosopher->has_eaten = 0;
		philosopher->has_slept = 0;
		philosopher->has_thought = 1;
	}
	else
	{
		philosopher->has_eaten = 0;
		philosopher->has_slept = 1;
		philosopher->has_thought = 0;
	}
	philosopher->is_dead = 0;
}

void	init_philosophers(t_table *table)
{
	int	i;

	table->philosophers = malloc(table->nb_philo * sizeof(t_philo));
	table->forks = malloc(table->nb_philo * sizeof(pthread_mutex_t));
	i = -1;
	while (++i < table->nb_philo)
		pthread_mutex_init(&table->forks[i], NULL);
	i = -1;
	while (++i < table->nb_philo)
	{
		table->philosophers[i].id = i + 1;
		table->philosophers[i].fork_left = &table->forks[i];
		if (i == table->nb_philo - 1)
			table->philosophers[i].fork_right = &table->forks[0];
		else
			table->philosophers[i].fork_right = &table->forks[i + 1];
		init_values(&table->philosophers[i]);
		table->philosophers[i].one_died = &table->dead;
	}
}
