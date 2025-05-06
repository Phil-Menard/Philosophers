/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:52:33 by pmenard           #+#    #+#             */
/*   Updated: 2025/05/06 15:58:17 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display_instruction(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->print_mutex);
	gettimeofday(&philo->timer->end_time, NULL);
	philo->timer->elapsed_ms = calcul_elapsed_time(philo);
	if (*philo->one_died == 0)
		printf("%ld %d %s\n", philo->timer->elapsed_ms, philo->id, str);
	pthread_mutex_unlock(philo->print_mutex);
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(philo->death_mutex);
	pthread_mutex_lock(philo->print_mutex);
	gettimeofday(&philo->starve_timer.end_time, NULL);
	philo->starve_timer.elapsed_ms = calcul_starving_time(philo);
	if (*philo->is_dead == 0
		&& philo->starve_timer.elapsed_ms >= philo->time_to_die)
	{
		gettimeofday(&philo->timer->end_time, NULL);
		philo->timer->elapsed_ms = calcul_elapsed_time(philo);
		printf("%ld %d died\n", philo->timer->elapsed_ms, philo->id);
		*philo->is_dead = 1;
		pthread_mutex_unlock(philo->print_mutex);
		pthread_mutex_unlock(philo->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->print_mutex);
	pthread_mutex_unlock(philo->death_mutex);
	return (0);
}

int	check_philos(t_table *table)
{
	int		i;
	long	last_meal;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_lock(table->philosophers[i].meal_mutex);
		gettimeofday(table->philosophers[i].meal_timer.end_time, NULL);
		last_meal = calcul_starving_time(table->philosophers[i]);
		pthread_mutex_unlock(table->philosophers[i].meal_mutex);
		if (last_meal >= table->philosophers[i].time_to_die)
			return (1);
		i++;
	}
	return (0);
}

void	go_eat(t_philo *philo)
{
	display_instruction(philo, "is eating");
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_lock(philo->meal_mutex);
	philo->nb_time_must_eat = count_meals(philo);
	pthread_mutex_unlock(philo->meal_mutex);
}

void	go_sleep(t_philo *philo)
{
	display_instruction(philo, "is sleeping");
}

void	go_think(t_philo *philo)
{
	display_instruction(philo, "is thinking");
}
