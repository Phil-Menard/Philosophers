/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:30:27 by pmenard           #+#    #+#             */
/*   Updated: 2025/05/07 12:16:38 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

long	get_current_time(void)
{
	struct timeval	timer;
	long			x;

	gettimeofday(&timer, NULL);
	x = (timer.tv_sec * 1000) + (timer.tv_usec / 1000);
	return (x);
}

void	omg_one_died(t_philo *philo)
{
	long	timer;

	pthread_mutex_lock(philo->print_mutex);
	pthread_mutex_lock(philo->death_mutex);
	timer = get_current_time() - philo->start_timer;
	*philo->dead = 1;
	printf("%ld %d died\n", timer, philo->id);
	pthread_mutex_unlock(philo->print_mutex);
	pthread_mutex_unlock(philo->death_mutex);
}

void	enough_meals(t_table *table)
{
	pthread_mutex_lock(&table->death_mutex);
	table->dead = 1;
	pthread_mutex_unlock(&table->death_mutex);
}
