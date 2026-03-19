/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 13:34:44 by thlibers          #+#    #+#             */
/*   Updated: 2026/03/19 12:38:41 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

static bool	check_philo_dead(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		if (get_mstime() - table->philos[i].last_meal_time > table->time_to_die)
		{
			pthread_mutex_lock(table->death_mutex);
			table->is_dead = true;
			pthread_mutex_unlock(table->death_mutex);
			pthread_mutex_lock(table->print_mutex);
			printf("%d %d died\n", get_mstime() - table->start_time,
				table->philos[i].id);
			pthread_mutex_unlock(table->print_mutex);
			return (true);
		}
		i++;
	}
	return (false);
}

static bool	check_all_ate(t_table *table)
{
	int	i;

	if (table->nb_meals <= 0)
		return (false);
	i = 0;
	while (i < table->nb_philos)
	{
		if (table->philos[i].meals_eaten < table->nb_meals)
			return (false);
		i++;
	}
	pthread_mutex_lock(table->death_mutex);
	*table->shut_up = true;
	pthread_mutex_unlock(table->death_mutex);
	return (true);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (1)
	{
		if (check_philo_dead(table))
			break ;
		if (check_all_ate(table))
			break ;
		usleep(500);
	}
	return (NULL);
}
