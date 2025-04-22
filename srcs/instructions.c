/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:52:33 by pmenard           #+#    #+#             */
/*   Updated: 2025/04/22 18:29:43 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display_instruction(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->print_mutex);
	gettimeofday(&philo->timer.end_time, NULL);
	philo->timer.elapsed_ms = calcul_elapsed_time(philo);
	if (*philo->one_died == 0)
		printf("%ld %d %s\n", philo->timer.elapsed_ms, philo->id, str);
	pthread_mutex_unlock(philo->print_mutex);
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(philo->death_mutex);
	pthread_mutex_lock(philo->print_mutex);
	gettimeofday(&philo->starve_timer.end_time, NULL);
	philo->starve_timer.elapsed_ms = calcul_starving_time(philo);
	if (*philo->one_died == 0
		&& philo->starve_timer.elapsed_ms >= philo->time_to_die)
	{
		gettimeofday(&philo->timer.end_time, NULL);
		philo->timer.elapsed_ms = calcul_elapsed_time(philo);
		printf("%ld %d died\n", philo->timer.elapsed_ms, philo->id);
		*philo->one_died = 1;
		pthread_mutex_unlock(philo->print_mutex);
		pthread_mutex_unlock(philo->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->print_mutex);
	pthread_mutex_unlock(philo->death_mutex);
	return (0);
}

void	go_eat(t_philo *philo)
{
	if (take_fork(philo) == 1)
		return ;
	gettimeofday(&philo->starve_timer.start_time, NULL);
	display_instruction(philo, "is eating");
	if (monitor_instructions(philo, philo->time_to_eat) == 1)
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		return ;
	}
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_lock(philo->meal_mutex);
	philo->nb_time_must_eat = count_meals(philo);
	pthread_mutex_unlock(philo->meal_mutex);
}

void	go_sleep(t_philo *philo)
{
	display_instruction(philo, "is sleeping");
	if (monitor_instructions(philo, philo->time_to_sleep) == 1)
		return ;
}

void	go_think(t_philo *philo)
{
	if ((philo->time_to_die - philo->time_to_eat - philo->time_to_sleep)
		>= 10)
		usleep(2000);
	display_instruction(philo, "is thinking");
}
