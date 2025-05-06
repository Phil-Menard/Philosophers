/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:52:33 by pmenard           #+#    #+#             */
/*   Updated: 2025/05/06 18:58:01 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display_instruction(t_philo *philo, char *str)
{
	long	timer;

	timer = get_current_time() - philo->start_timer;
	pthread_mutex_lock(philo->print_mutex);
	pthread_mutex_lock(philo->death_mutex);
	if (*philo->dead == 0)
		printf("%ld %d %s\n", timer, philo->id, str);
	pthread_mutex_unlock(philo->death_mutex);
	pthread_mutex_unlock(philo->print_mutex);
}

void	go_eat(t_philo *philo)
{
	display_instruction(philo, "is eating");
	pthread_mutex_lock(philo->meal_mutex);
	philo->last_meal = get_current_time();
	philo->nb_meal++;
	pthread_mutex_unlock(philo->meal_mutex);
	monitor_instructions(philo->time_to_eat);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

void	go_sleep(t_philo *philo)
{
	display_instruction(philo, "is sleeping");
	monitor_instructions(philo->time_to_sleep);
}

void	go_think(t_philo *philo)
{
	display_instruction(philo, "is thinking");
}

//main loop that keep philosophers living and doing things
void	*handle_threads(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (1)
	{
		if (check_if_dead(philo) == 1)
			break ;
		if (take_fork(philo) == 1)
			break ;
		go_eat(philo);
		go_sleep(philo);
		go_think(philo);
	}
	return (NULL);
}
