/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_instructions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:35:10 by pmenard           #+#    #+#             */
/*   Updated: 2025/05/06 18:55:19 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->death_mutex);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->death_mutex);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(philo->death_mutex);
		return (0);
	}
}

int	one_philo(t_philo *philo)
{
	if (philo->fork_left == philo->fork_right)
	{
		while (check_if_dead(philo) == 0)
			usleep(100);
		return (1);
	}
	else
		return (0);
}

void	monitor_instructions(int time_to_wait)
{
	long	x;

	x = get_current_time() + (long) time_to_wait;
	while (get_current_time() < x)
		usleep(500);
}

int	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->fork_right);
		display_instruction(philo, "has taken a fork");
		if (one_philo(philo) == 1)
			return (pthread_mutex_unlock(philo->fork_right), 1);
		pthread_mutex_lock(philo->fork_left);
		display_instruction(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->fork_left);
		display_instruction(philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_right);
		display_instruction(philo, "has taken a fork");
	}
	return (0);
}
