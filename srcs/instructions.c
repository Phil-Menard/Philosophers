/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:52:33 by pmenard           #+#    #+#             */
/*   Updated: 2025/02/18 18:23:33 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	go_eat(t_philo *philo)
{
	if (*philo->one_died == 0)
	{
		pthread_mutex_lock(philo->fork_left);
		printf("%d has taken his left fork\n", philo->id);
		pthread_mutex_lock(philo->fork_right);
		printf("%d has taken his right fork\n", philo->id);
		usleep(philo->time_to_eat);
		printf("%d finished eating\n", philo->id);
		philo->has_thought = 0;
		philo->has_eaten = 1;
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
	}
}

void	go_sleep(t_philo *philo)
{
	if (*philo->one_died == 0)
	{
		printf("%d is sleeping\n", philo->id);
		usleep(philo->time_to_sleep);
		philo->has_eaten = 0;
		philo->has_slept = 1;
		philo->is_dead = 1;
		*philo->one_died = 1;
	}
}

void	go_think(t_philo *philo)
{
	if (*philo->one_died == 0)
	{
		printf("%d is thinking\n", philo->id);
		usleep(philo->time_to_think);
		philo->has_slept = 0;
		philo->has_thought = 1;
	}
}
