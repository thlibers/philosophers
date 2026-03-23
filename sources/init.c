/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 13:34:40 by thlibers          #+#    #+#             */
/*   Updated: 2026/03/23 17:44:53 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

static void	destroy_forks(pthread_mutex_t *forks, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

static bool	init_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
		{
			destroy_forks(table->forks, i);
			return (false);
		}
		i++;
	}
	return (true);
}

static void	assign_forks(t_philo *philo, t_table *table, int i)
{
	philo->left_fork = &table->forks[i];
	philo->right_fork = &table->forks[(i + 1) % table->nb_philos];
	if (i % 2 == 1)
	{
		philo->left_fork = &table->forks[(i + 1) % table->nb_philos];
		philo->right_fork = &table->forks[i];
	}
}

static bool	init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals_eaten = 0;
		table->philos[i].last_meal_time = 0;
		table->philos[i].table = table;
		table->philos[i].last_eat = malloc(sizeof(pthread_mutex_t));
		table->philos[i].nb_eaten = malloc(sizeof(pthread_mutex_t));
		if (!table->philos[i].last_eat || !table->philos[i].nb_eaten)
			return (false);
		if (pthread_mutex_init(table->philos[i].last_eat, NULL)
			|| pthread_mutex_init(table->philos[i].nb_eaten, NULL))
			return (false);
		assign_forks(&table->philos[i], table, i);
		i++;
	}
	return (true);
}

bool	init_table(t_table *table)
{
	table->start_time = 0;
	table->done = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philos);
	table->philos = malloc(sizeof(t_philo) * table->nb_philos);
	table->print_mutex = malloc(sizeof(pthread_mutex_t));
	table->done_mutex = malloc(sizeof(pthread_mutex_t));
	table->shutup_mutex = malloc(sizeof(pthread_mutex_t));
	if (!table->forks || !table->philos || !table->print_mutex
		|| !table->done_mutex || !table->shutup_mutex)
		return (false);
	if (pthread_mutex_init(table->print_mutex, NULL))
		return (false);
	if (pthread_mutex_init(table->done_mutex, NULL)
		|| pthread_mutex_init(table->shutup_mutex, NULL))
		return (pthread_mutex_destroy(table->print_mutex), false);
	if (!init_forks(table))
	{
		pthread_mutex_destroy(table->print_mutex);
		pthread_mutex_destroy(table->done_mutex);
		pthread_mutex_destroy(table->shutup_mutex);
		return (false);
	}
	if (!init_philos(table))
		return (false);
	return (true);
}
