/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 13:34:53 by thlibers          #+#    #+#             */
/*   Updated: 2026/03/19 12:38:59 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

long	ft_atol(const char *nptr)
{
	int			i;
	long		res;

	i = 0;
	res = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	return (res);
}

void	safe_print(t_table *table, char *str, int nb)
{
	int	elapsed;
	
	pthread_mutex_lock(table->print_mutex);
	if (*table->shut_up)
	{
		pthread_mutex_unlock(table->print_mutex);
		return ;
	}
	elapsed = get_mstime() - table->start_time;
	printf("%d %d %s\n", elapsed, table->philos->id, str);
	pthread_mutex_unlock(table->print_mutex);
}

int	get_mstime(void)
{
	struct timeval	time;
	int				ms;

	gettimeofday(&time, NULL);
	ms = (int)(time.tv_sec * 1000 + time.tv_usec / 1000);
	return (ms);
}

bool	check_die(t_table *table)
{
	pthread_mutex_lock(table->death_mutex);
	if (table->is_dead)
		return (pthread_mutex_unlock(table->death_mutex), true);
	return (pthread_mutex_unlock(table->death_mutex), false);
}
