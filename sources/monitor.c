/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 13:34:44 by thlibers          #+#    #+#             */
/*   Updated: 2026/03/23 17:34:25 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

static bool	check_philo_dead(t_table *table)
{
	int		i;
	long	last_meal;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_lock(table->philos[i].last_eat);
		last_meal = table->philos[i].last_meal_time;
		pthread_mutex_unlock(table->philos[i].last_eat);
		if (last_meal != 0 && get_mstime() - last_meal > table->time_to_die)
		{
			pthread_mutex_lock(table->shutup_mutex);
			table->shut_up = true;
			pthread_mutex_unlock(table->shutup_mutex);
			pthread_mutex_lock(table->print_mutex);
			printf("%ld %d died\n", get_mstime() - table->start_time,
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
	int	meals;

	if (table->nb_meals <= 0)
		return (false);
	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_lock(table->philos[i].nb_eaten);
		meals = table->philos[i].meals_eaten;
		pthread_mutex_unlock(table->philos[i].nb_eaten);
		if (meals < table->nb_meals)
			return (false);
		i++;
	}
	pthread_mutex_lock(table->shutup_mutex);
	table->shut_up = true;
	pthread_mutex_unlock(table->shutup_mutex);
	return (true);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (1 && table->nb_philos > 1)
	{
		if (check_philo_dead(table))
			break ;
		if (check_all_ate(table))
			break ;
		usleep(500);
	}
	return (NULL);
}
