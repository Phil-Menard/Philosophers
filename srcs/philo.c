/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:58:36 by pmenard           #+#    #+#             */
/*   Updated: 2025/04/22 10:08:28 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//main loop that keep philosophers living and doing things
void	*handle_threads(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	gettimeofday(&philo->timer.start_time, NULL);
	gettimeofday(&philo->starve_timer.start_time, NULL);
	while (*philo->one_died == 0 && *philo->ate_enough < philo->nb_philo)
	{
		go_eat(philo);
		go_sleep(philo);
		go_think(philo);
	}
	return (NULL);
}

int	end_philosophers(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nb_philo)
	{
		if (pthread_join(table->philosophers[i].thread, NULL))
		{
			printf("Erreur lors de l'attente du thread.\n");
			free_all(table);
			return (1);
		}
	}
	return (0);
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
			free_all(table);
			return (1);
		}
	}
	if (end_philosophers(table) == -1)
		return (1);
	return (0);
}

int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (atoi(argv[i]) <= 0)
		{
			printf("%s should be > 0. ", argv[i]);
			printf("Otherwise it is not possible!\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
	{
		printf("Should be ./philo number_of_philosophers time_to_die time_to_");
		printf("eat time_to_sleep [number_of_times_each_philosopher_must_eat]");
		printf(" (optionnal argument)\n");
		return (1);
	}
	if (check_args(argc, argv) == -1)
		return (1);
	table.nb_philo = ft_atoi(argv[1]);
	table.dead = 0;
	init_philosophers(&table, argv);
	if (start_philosophers(&table) == 1)
		return (1);
	free_all(&table);
}

/*

Ensure the code of philo complies with the following requirements and 
ask for explanations.

Check if there is a mutex per fork and that it's used to check the 
fork value and/or change it.

Check the outputs are never mixed up.

Check how the death of a philosopher is verified and if there is a 
mutex to prevent a philosopher
from dying and starting eating at the same time.

Test 1 800 200 200. The philosopher should not eat and should die.

Test 5 800 200 200. No philosopher should die.

Test 5 800 200 200 7. No philosopher should die and
the simulation should stop when every philosopher has eaten at least 7 times.

Test 4 410 200 200. No philosopher should die.

Test 4 310 200 100. One philosopher should die.
*/