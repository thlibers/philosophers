/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 13:34:37 by thlibers          #+#    #+#             */
/*   Updated: 2026/03/19 13:21:23 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

bool	ft_take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	safe_print(philo->table, "has taken a fork", philo->id);
	pthread_mutex_lock(philo->right_fork);
	safe_print(philo->table, "has taken a fork", philo->id);
	return (true);
}

bool	ft_eat(t_philo *philo)
{
	int	start_eat;

	start_eat = get_mstime();
	philo->last_meal_time = start_eat;
	philo->meals_eaten++;
	safe_print(philo->table, "is eating", philo->id);
	while (get_mstime() - start_eat < philo->table->time_to_eat)
	{
		if (check_die(philo->table))
			return (false);
		usleep(100);
	}
	return (true);
}

bool	ft_think(t_philo *philo)
{
	safe_print(philo->table, "is thinking", philo->id);
	return (true);
}

bool	ft_sleep(t_philo *philo)
{
	int	start_sleep;

	start_sleep = get_mstime();
	safe_print(philo->table, "is sleeping", philo->id);
	while (get_mstime() - start_sleep < philo->table->time_to_sleep)
	{
		if (check_die(philo->table))
			return (false);
		usleep(100);
	}
	return (true);
}

bool	ft_drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
