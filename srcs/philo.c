/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:58:36 by pmenard           #+#    #+#             */
/*   Updated: 2025/02/17 12:01:55 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philosophers(t_table *table, int nb_philo)
{
	int	i;

	table->philosophers = malloc(nb_philo * sizeof(t_philo));
	table->forks = malloc(nb_philo * sizeof(pthread_mutex_t));
	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < nb_philo)
	{
		table->philosophers[i].id = i + 1;
		table->philosophers[i].fork_left = &table->forks[i];
		if (i == nb_philo - 1)
			table->philosophers[i].fork_right = &table->forks[0];
		else
			table->philosophers[i].fork_right = &table->forks[i + 1];
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_table	table;
	int		nb_philo;
	int		i;

	(void) argc;
	nb_philo = ft_atoi(argv[1]);
	init_philosophers(&table, nb_philo);
	printf("%d\n", table.philosophers[0].id);
	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_destroy(&table.forks[i]);
		i++;
	}
	free(table.philosophers);
	free(table.forks);
	return (0);
}
