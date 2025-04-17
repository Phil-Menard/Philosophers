/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:30:27 by pmenard           #+#    #+#             */
/*   Updated: 2025/04/17 14:40:02 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//free some philosophers and destroy some mutexes
void	free_some(t_table *table, int i)
{
	while (--i >= 0)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philosophers[i].death_mutex);
	}
	free(table->philosophers);
	free(table->forks);
}

//free all philosophers and destroy all mutexes
void	free_all(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->philosophers);
	free(table->forks);
}

int	ft_atoi(const char *nptr)
{
	int	result;
	int	sign;

	sign = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '+')
		nptr++;
	else if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	result = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = (result * 10) + (*nptr - '0');
		nptr++;
	}
	result *= sign;
	return (result);
}

/* long	calcul_elapsed_time(t_philo *philo)
{
	long	x;

	x = (philo->timer.end_time.tv_sec
		- philo->timer.start_time.tv_sec) * 1000
	+ (philo->timer.end_time.tv_usec - philo->timer.start_time.tv_usec + 500)
		/ 1000;
	return (x);
}
 */