/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 13:34:40 by thlibers          #+#    #+#             */
/*   Updated: 2026/03/17 15:15:36 by thlibers         ###   ########.fr       */
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
	pthread_mutex_t	*left;
    pthread_mutex_t	*right;

    left = &table->forks[i];
    right = &table->forks[(i + 1) % table->nb_philos];
    if (i % 2 == 0)
    {
        philo->left_fork = left;
        philo->right_fork = right;
    }
    else
    {
        philo->left_fork = right;
        philo->right_fork = left;
    }
}

static void	init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		table->philos[i].id = i + 1;
        table->philos[i].meals_eaten = 0;
        table->philos[i].last_meal_time = 0;
        table->philos[i].table = table;
        assign_forks(&table->philos[i], table, i);
        i++;
	}
}

bool	init_table(t_table *table)
{
	table->is_dead = false;
	table->start_time = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philos);
	table->philos = malloc(sizeof(t_philo) * table->nb_philos);
	if (!table->forks || !table->philos)
        return (false);
    if (pthread_mutex_init(&table->print_mutex, NULL))
        return (false);
    if (pthread_mutex_init(&table->death_mutex, NULL))
    {
        pthread_mutex_destroy(&table->print_mutex);
        return (false);
    }
    if (!init_forks(table))
    {
        pthread_mutex_destroy(&table->print_mutex);
        pthread_mutex_destroy(&table->death_mutex);
        return (false);
    }
    init_philos(table);
    return (true);
}
