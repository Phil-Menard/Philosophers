/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:58:36 by pmenard           #+#    #+#             */
/*   Updated: 2025/02/13 12:00:59 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*increment_counter(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	printf("forks : %d\n", *philo->forks);
	if (*philo->forks > 1)
	{
		pthread_mutex_lock(philo->mutex);
		*philo->forks -= 2;
		pthread_mutex_unlock(philo->mutex);
		printf("philo %d took 2 forks to eat\n", philo->id);
	}
	else
	{
		printf("Not enough forks left for philo %d\n", philo->id);
	}
	return (NULL);
}

int	main(void)
{
	pthread_t		*threads;
	t_philo			*philo;
	pthread_mutex_t	mutex;
	int				nb_philos;
	int				i;

	nb_philos = 5;
	threads = malloc(nb_philos * sizeof(pthread_t));
	philo = malloc(nb_philos * sizeof(t_philo));
	printf("Valeur initiale de forks : %d\n", nb_philos);
	if (pthread_mutex_init(&mutex, NULL) != 0)
	{
		printf("Erreur lors de l'initialisation du mutex.\n");
		return (1);
	}
	i = 0;
	while (i < 5)
	{
		philo[i].id = i + 1;
		philo[i].mutex = &mutex;
		philo[i].forks = &nb_philos;
		if (pthread_create(&threads[i], NULL, increment_counter, &philo[i]))
		{
			printf("Erreur lors de la creation du thread\n");
			pthread_mutex_destroy(&mutex);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < 5)
	{
		if (pthread_join(threads[i], NULL))
		{
			printf("Erreur lors de l'attente' du thread\n");
			pthread_mutex_destroy(&mutex);
			return (2);
		}
		i++;
	}
	printf("Valeur finale de forks : %d\n", nb_philos);
	pthread_mutex_destroy(&mutex);
	return (0);
}
