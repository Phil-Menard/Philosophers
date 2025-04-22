/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_instructions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:35:10 by pmenard           #+#    #+#             */
/*   Updated: 2025/04/22 10:01:30 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

void	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->fork_right);
		display_instruction(philo, "has taken a fork");
		if (one_philo(philo) == 1)
			return ;
		pthread_mutex_lock(philo->fork_left);
		if (check_death(philo) == 1)
			return (unlock_forks(philo));
		display_instruction(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->fork_left);
		display_instruction(philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_right);
		if (check_death(philo) == 1)
			return (unlock_forks(philo));
		display_instruction(philo, "has taken a fork");
	}
}

int	monitor_instructions(t_philo *philo, int time_to_wait)
{
	struct s_time	time;
	int				x;

	gettimeofday(&time.start_time, NULL);
	x = 0;
	while (x < time_to_wait)
	{
		usleep(500);
		if (*philo->one_died == 1)
			return (1);
		gettimeofday(&time.end_time, NULL);
		x = (time.end_time.tv_sec
				- time.start_time.tv_sec) * 1000
			+ (time.end_time.tv_usec - time.start_time.tv_usec) / 1000;
	}
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
