/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:20:48 by pmenard           #+#    #+#             */
/*   Updated: 2025/05/06 13:17:31 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//free some philosophers and destroy some mutexes
void	free_some(t_table *table, int i)
{
	while (--i >= 0)
	{
		pthread_mutex_destroy(&table->forks[i]);
	}
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->death_mutex);
	pthread_mutex_destroy(&table->meal_mutex);
	pthread_mutex_destroy(&table->ready_mutex);
	pthread_mutex_destroy(&table->time_mutex);
	pthread_mutex_destroy(&table->check_fork_mutex);
	free(table->philosophers);
	free(table->forks);
	free(table->check_fork);
}

//free all philosophers and destroy all mutexes
void	free_all(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->death_mutex);
	pthread_mutex_destroy(&table->meal_mutex);
	pthread_mutex_destroy(&table->ready_mutex);
	pthread_mutex_destroy(&table->time_mutex);
	pthread_mutex_destroy(&table->check_fork_mutex);
	free(table->philosophers);
	free(table->forks);
	free(table->check_fork);
}
