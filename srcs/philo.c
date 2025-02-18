/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:58:36 by pmenard           #+#    #+#             */
/*   Updated: 2025/02/18 16:18:10 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*handle_threads(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (*philo->one_died == 0)
	{
		if (philo->has_thought == 1)
			go_eat(philo);
		else if (philo->has_slept == 1)
			go_think(philo);
		else if (philo->has_eaten == 1)
			go_sleep(philo);
	}
	return (NULL);
}

int	end_philosophers(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nb_philo)
	{
		//table->philosophers[i].is_dead == 0 && 
		if (pthread_join(table->philosophers[i].thread, NULL))
		{
			printf("Erreur lors de l'attente du thread.\n");
			free_all(table);
			return (1);
		}
		/* else if (table->philosophers[i].is_dead == 1)
		{
			printf("%d died\n", table->philosophers[i].id);
			if (pthread_detach(table->philosophers[i].thread))
			{
				printf("Erreur lors du detachement du thread.\n");
				return (1);
			}
		} */
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
	if (check_args(argc, argv) == - 1)
		return (1);
	table.nb_philo = ft_atoi(argv[1]);
	table.dead = 0;
	init_philosophers(&table, argv);
	if (gettimeofday(&table.time_ms.start_time, NULL) != 0)
	{
		printf("Erreur lors de l'appel à gettimeofday");
		return 1;
	}
	if (start_philosophers(&table) == 1)
		return (1);
	if (gettimeofday(&table.time_ms.end_time, NULL) != 0)
	{
		printf("Erreur lors de l'appel à gettimeofday");
		return 1;
	}
	free_all(&table);
	table.time_ms.ellapsed_ms = (table.time_ms.end_time.tv_sec - table.time_ms.start_time.tv_sec * 1000)
		+ (table.time_ms.end_time.tv_usec - table.time_ms.start_time.tv_usec / 1000);
	printf("Temps ecoule : %ld ms\n", table.time_ms.ellapsed_ms);
}
