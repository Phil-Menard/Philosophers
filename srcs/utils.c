/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:30:27 by pmenard           #+#    #+#             */
/*   Updated: 2025/05/06 11:05:45 by pmenard          ###   ########.fr       */
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

long	calcul_elapsed_time(t_philo *philo)
{
	long	x;

	x = (philo->timer->end_time.tv_sec
			- philo->timer->start_time.tv_sec) * 1000
		+ (philo->timer->end_time.tv_usec - philo->timer->start_time.tv_usec)
		/ 1000;
	return (x);
}

long	calcul_starving_time(t_philo *philo)
{
	long	x;

	x = (philo->starve_timer.end_time.tv_sec
			- philo->starve_timer.start_time.tv_sec) * 1000
		+ (philo->starve_timer.end_time.tv_usec
			- philo->starve_timer.start_time.tv_usec) / 1000;
	return (x);
}

int	one_philo(t_philo *philo)
{
	if (philo->fork_left == philo->fork_right)
	{
		while (check_death(philo) == 0)
			usleep(100);
		return (1);
	}
	else
		return (0);
}

int	count_meals(t_philo *philo)
{
	if (philo->nb_time_must_eat == -1)
		return (-1);
	if (philo->nb_time_must_eat > 0)
		philo->nb_time_must_eat--;
	if (philo->nb_time_must_eat == 0)
	{
		*philo->ate_enough += 1;
		philo->nb_time_must_eat--;
	}
	return (philo->nb_time_must_eat);
}
