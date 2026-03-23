/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:49:28 by thlibers          #+#    #+#             */
/*   Updated: 2026/03/23 17:13:59 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

void	destroy_table(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(table->philos[i].last_eat);
		pthread_mutex_destroy(table->philos[i].nb_eaten);
		free(table->philos[i].last_eat);
		free(table->philos[i].nb_eaten);
		i++;
	}
	pthread_mutex_destroy(table->print_mutex);
	pthread_mutex_destroy(table->done_mutex);
	pthread_mutex_destroy(table->shutup_mutex);
	free(table->forks);
	free(table->philos);
	free(table->print_mutex);
	free(table->done_mutex);
	free(table->shutup_mutex);
}
