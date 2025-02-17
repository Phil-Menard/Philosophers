/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:53:51 by pmenard           #+#    #+#             */
/*   Updated: 2025/02/17 17:55:52 by pmenard          ###   ########.fr       */
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
		table->philosophers[i].has_eaten = 0;
		table->philosophers[i].is_eating = 0;
		table->philosophers[i].is_sleeping = 0;
		table->philosophers[i].is_thinking = 0;
		i++;
	}
}
