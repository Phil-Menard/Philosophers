/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:58:36 by pmenard           #+#    #+#             */
/*   Updated: 2025/02/17 17:56:30 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*handle_threads(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->id % 2 == 0 && philo->has_eaten == 0)
		eat(philo);
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
