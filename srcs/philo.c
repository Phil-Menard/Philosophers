/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:58:36 by pmenard           #+#    #+#             */
/*   Updated: 2025/05/06 18:15:36 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philos(t_table *table)
{
	int		i;
	int		temp_nb_meal;
	long	temp_last_meal;
	int		total_meal;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_lock(table->philosophers[i].meal_mutex);
		temp_nb_meal = table->philosophers[i].nb_meal;
		temp_last_meal = table->philosophers[i].last_meal;
		pthread_mutex_unlock(table->philosophers[i].meal_mutex);
		if (table->required_meal != -1 && temp_nb_meal >= table->required_meal)
			total_meal++;
		if (total_meal == table->nb_philo)
			return (1);
		if ((get_current_time() - temp_last_meal)
			> table->philosophers[i].time_to_die)
		{
			omg_one_died(&table->philosophers[i]);
			return (1);
		}
		i++;
	}
	return (0);
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
	gettimeofday(&table.global_timer.start_time, NULL);
	set_timer_start(&table);
	if (start_philosophers(&table) == 1)
		return (1);
	while (1)
	{
		if (check_philos(&table) != 0)
			break ;
	}
	end_philosophers(&table);
	free_all(&table);
}
