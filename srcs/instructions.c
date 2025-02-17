/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:52:33 by pmenard           #+#    #+#             */
/*   Updated: 2025/02/17 17:44:09 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	printf("%d has taken his left fork\n", philo->id);
	pthread_mutex_lock(philo->fork_right);
	printf("%d has taken his right fork\n", philo->id);
	philo->is_eating = 1;
	usleep(5000);
	printf("%d finished eating\n", philo->id);
	philo->is_eating = 0;
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}
