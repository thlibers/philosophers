/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 13:34:37 by thlibers          #+#    #+#             */
/*   Updated: 2026/03/23 17:30:29 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

bool	ft_take_forks(t_philo *philo, pthread_mutex_t **first_fork,
		pthread_mutex_t **second_fork)
{
	*first_fork = philo->left_fork;
	*second_fork = philo->right_fork;
	if (*first_fork > *second_fork)
	{
		*first_fork = philo->right_fork;
		*second_fork = philo->left_fork;
	}
	pthread_mutex_lock(*first_fork);
	if (check_done(philo) == true)
	{
		pthread_mutex_unlock(*first_fork);
		return (true);
	}
	safe_print(philo->table, "has taken a fork", philo->id);
	pthread_mutex_lock(*second_fork);
	if (check_done(philo) == true)
	{
		pthread_mutex_unlock(*second_fork);
		pthread_mutex_unlock(*first_fork);
		return (true);
	}
	safe_print(philo->table, "has taken a fork", philo->id);
	return (false);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (ft_take_forks(philo, &first_fork, &second_fork) == true)
		return ;
	safe_print(philo->table, "is eating", philo->id);
	pthread_mutex_lock(philo->last_eat);
	philo->last_meal_time = get_mstime();
	pthread_mutex_unlock(philo->last_eat);
	pthread_mutex_lock(philo->nb_eaten);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->nb_eaten);
	better_usleep(philo->table->time_to_eat, philo);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}

void	ft_think(t_philo *philo)
{
	long	think_time;

	safe_print(philo->table, "is thinking", philo->id);
	think_time = (philo->table->time_to_die - philo->table->time_to_eat
			- philo->table->time_to_sleep) / 2;
	if (think_time > 0 && think_time < 200)
		better_usleep(think_time, philo);
	else if (philo->table->nb_philos % 2 == 1)
		usleep(500);
}

void	ft_sleep(t_philo *philo)
{
	if (check_done(philo) == true)
		return ;
	safe_print(philo->table, "is sleeping", philo->id);
	better_usleep(philo->table->time_to_sleep, philo);
}

void	ft_die(t_philo *philo)
{
	if (check_done(philo) == true)
		return ;
	safe_print(philo->table, "died", philo->id);
}
