/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:58:36 by pmenard           #+#    #+#             */
/*   Updated: 2025/02/12 16:58:42 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*increment_counter(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *) arg;
	i = 0;
	while (i < 1000)
	{
		pthread_mutex_lock(&philo->mutex);
		++philo->counter;
		pthread_mutex_unlock(&philo->mutex);
		i++;
	}
	printf("thread termine\n");
	return (NULL);
}

int	main(void)
{
	t_philo		philo;
	int			nb_philos;
	int			i;

	nb_philos = 5;
	philo.thread = malloc(nb_philos * sizeof(pthread_t));
	philo.counter = 0;
	if (pthread_mutex_init(&philo.mutex, NULL) != 0)
	{
		fprintf(stderr, "Erreur lors de l'initialisation du mutex.\n");
		return (1);
	}
	i = 0;
	while (i < nb_philos)
	{
		if (pthread_create(&philo.thread[i], NULL, increment_counter, &philo))
		{
			printf("Erreur lors de la creation du thread\n");
			pthread_mutex_destroy(&philo.mutex);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < nb_philos)
	{
		if (pthread_join(philo.thread[i], NULL))
		{
			printf("Erreur lors de l'attente' du thread\n");
			pthread_mutex_destroy(&philo.mutex);
			return (2);
		}
		i++;
	}
	printf("Valeur finale du compteur : %d\n", philo.counter);
	pthread_mutex_destroy(&philo.mutex);
	return (0);
}
