/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:58:36 by pmenard           #+#    #+#             */
/*   Updated: 2025/04/22 18:20:53 by pmenard          ###   ########.fr       */
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
	while (1)
	{
		go_eat(philo);
		if (check_meals(philo) == 1 || check_if_one_dead(philo) == 1)
			break ;
		go_sleep(philo);
		if (check_meals(philo) == 1 || check_if_one_dead(philo) == 1)
			break ;
		go_think(philo);
		if (check_meals(philo) == 1 || check_if_one_dead(philo) == 1)
			break ;
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
		if (ft_atoi(argv[i]) <= 0)
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
	if (check_args(argc, argv) == 1)
		return (1);
	table.nb_philo = ft_atoi(argv[1]);
	table.dead = 0;
	init_philosophers(&table, argv);
	if (start_philosophers(&table) == 1)
		return (1);
	free_all(&table);
}
