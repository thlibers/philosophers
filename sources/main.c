/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 13:34:42 by thlibers          #+#    #+#             */
/*   Updated: 2026/03/23 16:03:10 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

static void	start_simulation(t_table *table)
{
    int	i;

    table->start_time = get_mstime();
    i = 0;
    while (i < table->nb_philos)
    {
        pthread_create(&table->philos[i].thread, NULL, routine, &table->philos[i]);
        i++;
    }
    pthread_create(&table->monitor_thread, NULL, monitor_routine, table);
}

static void	wait_threads(t_table *table)
{
    int	i;

    i = 0;
    while (i < table->nb_philos)
    {
        pthread_join(table->philos[i].thread, NULL);
        i++;
    }
    pthread_join(table->monitor_thread, NULL);
}

static void	asign_table(t_table *table, int ac, long *args)
{
	table->shut_up = false;
    table->nb_philos = args[0];
    table->time_to_die = args[1];
    table->time_to_eat = args[2];
    table->time_to_sleep = args[3];
    if (ac == 6)
        table->nb_meals = args[4];
    else
        table->nb_meals = -1;
}

int	main(int ac, char **av)
{
	long	*args;
	t_table	table;
	
	if (ac < 5 || ac > 6)
		return (1);
	args = malloc(sizeof(long) * (ac - 1));
	if (!args || !parse(ac, av, args))
		return (free (args), 1);
	asign_table(&table, ac, args);
	if (!init_table(&table))
	{
		return (free (args), 1);
	}
	start_simulation(&table);
	wait_threads(&table);
	destroy_table(&table);
	free (args);
	return (0);
}
