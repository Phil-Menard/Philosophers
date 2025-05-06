/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_instructions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:35:10 by pmenard           #+#    #+#             */
/*   Updated: 2025/05/06 15:13:43 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_one_died(t_philo *philo)
{
	pthread_mutex_lock(philo->death_mutex);
	if (*philo->one_died == 1)
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

int	check_meals(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_mutex);
	if (*philo->ate_enough == philo->nb_philo)
	{
		pthread_mutex_unlock(philo->meal_mutex);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(philo->meal_mutex);
		return (0);
	}
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

int	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->fork_right);
		display_instruction(philo, "has taken a fork");
		if (one_philo(philo) == 1 || check_meals(philo) == 1
			|| check_death(philo) == 1)
			return (pthread_mutex_unlock(philo->fork_right), 1);
		pthread_mutex_lock(philo->fork_left);
		if (check_death(philo) == 1 || check_meals(philo) == 1)
			return (unlock_forks(philo), 1);
		display_instruction(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->fork_left);
		display_instruction(philo, "has taken a fork");
		if (check_death(philo) == 1 || check_meals(philo) == 1)
			return (pthread_mutex_unlock(philo->fork_left), 1);
		pthread_mutex_lock(philo->fork_right);
		if (check_death(philo) == 1 || check_meals(philo) == 1)
			return (unlock_forks(philo), 1);
		display_instruction(philo, "has taken a fork");
	}
	return (0);
}
