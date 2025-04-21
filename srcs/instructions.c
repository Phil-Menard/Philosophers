/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:52:33 by pmenard           #+#    #+#             */
/*   Updated: 2025/04/21 15:33:27 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	display_instruction(t_philo *philo, char *str)
{
	gettimeofday(&philo->timer.end_time, NULL);
	philo->timer.elapsed_ms = calcul_elapsed_time(philo);
	if (*philo->one_died == 0)
	{
		pthread_mutex_lock(philo->print_mutex);
		printf("%ld %d %s\n", philo->timer.elapsed_ms, philo->id, str);
		pthread_mutex_unlock(philo->print_mutex);
	}
	return (0);
}

int	check_death(t_philo *philo)
{
	gettimeofday(&philo->starve_timer.end_time, NULL);
	philo->starve_timer.elapsed_ms = calcul_starving_time(philo);
	// printf("check death : %d for philo %d\n", *philo->one_died, philo->id);
	pthread_mutex_lock(philo->death_mutex);
	if (*philo->one_died == 0
		&& philo->starve_timer.elapsed_ms >= philo->time_to_die)
	{
		gettimeofday(&philo->timer.end_time, NULL);
		philo->timer.elapsed_ms = calcul_elapsed_time(philo);
		printf("%ld %d died\n", philo->timer.elapsed_ms, philo->id);
		philo->is_dead = 1;
		*philo->one_died = 1;
		return (pthread_mutex_unlock(philo->death_mutex), 1);
	}
	pthread_mutex_unlock(philo->death_mutex);
	return (0);
}

int	go_eat(t_philo *philo)
{
	if (check_death(philo) == 1)
		return (1);
	pthread_mutex_lock(philo->fork_left);
	display_instruction(philo, "has taken a fork");
	if (check_death(philo) == 1)
		return (1);
	if (one_philo(philo) == 1)
		return (1);
	pthread_mutex_lock(philo->fork_right);
	display_instruction(philo, "has taken a fork");
	if (check_death(philo) == 1)
		return (1);
	gettimeofday(&philo->starve_timer.start_time, NULL);
	display_instruction(philo, "is eating");
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	philo->has_thought = 0;
	philo->has_eaten = 1;
	return (0);
}

int	go_sleep(t_philo *philo)
{
	if (check_death(philo) == 1)
		return (1);
	display_instruction(philo, "is sleeping");
	usleep(philo->time_to_sleep * 1000);
	if (check_death(philo) == 1)
		return (1);
	philo->has_eaten = 0;
	philo->has_slept = 1;
	return (0);
}

int	go_think(t_philo *philo)
{
	if (check_death(philo) == 1)
		return (1);
	display_instruction(philo, "is thinking");
	philo->has_slept = 0;
	philo->has_thought = 1;
	return (0);
}
