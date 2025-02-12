/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:01:01 by pmenard           #+#    #+#             */
/*   Updated: 2025/02/12 13:34:16 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *thread_function(void *arg)
{
	int value = *(int *)arg;
	printf("Bonjour depuis le thread ! Valeur reçue : %d\n", value);
	pthread_exit(NULL); // Termine le thread
}

pthread_t	*create_philo(int nb_philo)
{
	pthread_t	*philos;
	int			i;
	int			*arg;

	philos = malloc(nb_philo * sizeof(pthread_t));
	arg = malloc(nb_philo * sizeof(int));
	i = 0;
	while (i < nb_philo)
	{
		arg[i] = i * 10;
		if (pthread_create(&philos[i], NULL, thread_function, (void *)&arg[i]) != 0)
			printf("Erreur lors de la création du thread\n");
		i++;
	}
	return (philos);
}

int	main(void)
{
	pthread_t	*thread;
	int			nb_philo;

	nb_philo = 3;
	thread = create_philo(nb_philo);
	pthread_join(thread[0], NULL);
	printf("Le thread1 s'est termine\n");
	pthread_join(thread[1], NULL);
	printf("Le thread2 s'est termine\n");
	pthread_join(thread[2], NULL);
	printf("Le thread3 s'est termine\n");
	return (0);
}
