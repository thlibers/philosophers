/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 13:34:50 by thlibers          #+#    #+#             */
/*   Updated: 2026/03/23 15:55:09 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

static bool	has_finished(t_philo *philo)
{
	pthread_mutex_lock(philo->nb_eaten);
	if (philo->meals_eaten == philo->table->nb_meals)
	{
		pthread_mutex_unlock(philo->nb_eaten);
		pthread_mutex_lock(philo->table->done_mutex);
		philo->table->done++;
		pthread_mutex_unlock(philo->table->done_mutex);
		return (true);
	}
	pthread_mutex_unlock(philo->nb_eaten);
	return (false);
}

static void	ft_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	safe_print(philo->table, "has taken a fork", philo->id);
	usleep(philo->table->time_to_die * 1000);
	ft_die(philo);
	pthread_mutex_unlock(philo->left_fork);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->nb_philos == 1)
		return (ft_one_philo(philo), NULL);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (check_done(philo) == true)
			break ;
		ft_eat(philo);
		if (has_finished(philo) == true)
			break ;
		if (check_done(philo) == true)
			break ;
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}
