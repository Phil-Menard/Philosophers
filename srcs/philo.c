/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:58:36 by pmenard           #+#    #+#             */
/*   Updated: 2025/02/13 18:14:40 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philosophers(t_table *table, int nb_philo)
{
	int	i;

	table->philosophers = malloc(nb_philo * sizeof(t_philo));
	while (i < nb_philo)
	{
		table->philosophers->id = i + 1;
		// table->philosophers->left = 
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_table	table;
	int	nb_philo;

	(void) argc;
	nb_philo = ft_atoi(argv[1]);
	init_philosophers(&table);
	return (0);
}
