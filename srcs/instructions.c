/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:52:33 by pmenard           #+#    #+#             */
/*   Updated: 2025/02/20 14:42:34 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	display_instruction(t_philo *philo, char *str)
{
	if (gettimeofday(&philo->timer.end_time, NULL) != 0)
	{
		printf("Erreur lors de l'appel à gettimeofday");
		return (1);
	}
	philo->elapsed_time = (philo->timer.end_time.tv_sec
			- philo->timer.start_time.tv_sec) * 1000
		+ (philo->timer.end_time.tv_usec
			- philo->timer.start_time.tv_usec) / 1000;
	printf("%ld %d %s\n", philo->elapsed_time, philo->id, str);
	return (0);
}

int	go_eat(t_philo *philo)
{
	if (*philo->one_died == 0)
	{
		pthread_mutex_lock(philo->fork_left);
		display_instruction(philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_right);
		display_instruction(philo, "has taken a fork");
		display_instruction(philo, "is eating");
		usleep(philo->time_to_eat * 1000);
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		philo->has_thought = 0;
		philo->has_eaten = 1;
	}
	return (0);
}

int	go_sleep(t_philo *philo)
{
	if (*philo->one_died == 0)
	{
		display_instruction(philo, "is sleeping");
		usleep(philo->time_to_sleep * 1000);
		philo->has_eaten = 0;
		philo->has_slept = 1;
		/* philo->is_dead = 1;
		*philo->one_died = 1; */
	}
	return (0);
}

int	go_think(t_philo *philo)
{
	if (*philo->one_died == 0)
	{
		display_instruction(philo, "is thinking");
		usleep(philo->time_to_think * 1000);
		philo->has_slept = 0;
		philo->has_thought = 1;
	}
	return (0);
}
