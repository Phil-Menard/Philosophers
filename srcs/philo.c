/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:58:36 by pmenard           #+#    #+#             */
/*   Updated: 2025/05/06 15:47:39 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//main loop that keep philosophers living and doing things
void	*handle_threads(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	wait_threads(philo);
	while (1)
	{
		if (take_fork(philo) == 1)
			return ;
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
	i = -1;
	while (++i < table->nb_philo)
		gettimeofday(&table->philosophers[i].meal_timer.start_time, NULL);
	return (0);
}

int	check_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("Should be ./philo number_of_philosophers time_to_die ");
		printf("time_to_eat time_to_sleep [number_of_times_each_");
		printf("philosopher_must_eat] (optionnal argument)\n");
		return (1);
	}
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
	
	if (check_args(argc, argv) == 1)
		return (1);
	table.nb_philo = ft_atoi(argv[1]);
	table.dead = 0;
	init_philosophers(&table, argv);
	if (start_philosophers(&table) == 1)
		return (1);
	gettimeofday(&table.global_timer.start_time, NULL);
	while (1)
	{
		if (check_philos(&table) != 0)
			break ;
	}
	end_philosophers(&table);
	free_all(&table);
}
