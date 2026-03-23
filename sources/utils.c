/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 13:34:53 by thlibers          #+#    #+#             */
/*   Updated: 2026/03/23 17:43:48 by thlibers         ###   ########.fr       */
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
	long	elapsed;
	bool	should_print;

	pthread_mutex_lock(table->shutup_mutex);
	should_print = !table->shut_up;
	pthread_mutex_unlock(table->shutup_mutex);
	if (!should_print)
		return ;
	pthread_mutex_lock(table->print_mutex);
	elapsed = get_mstime() - table->start_time;
	printf("%ld %d %s\n", elapsed, nb, str);
	pthread_mutex_unlock(table->print_mutex);
}

long	get_mstime(void)
{
	struct timeval	time;
	long			ms;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec * 1000 + time.tv_usec / 1000);
	return (ms);
}

bool	check_done(t_philo *philo)
{
	pthread_mutex_lock(philo->table->shutup_mutex);
	if (philo->table->shut_up == true)
	{
		pthread_mutex_unlock(philo->table->shutup_mutex);
		return (true);
	}
	pthread_mutex_unlock(philo->table->shutup_mutex);
	return (false);
}

void	better_usleep(long duration_ms, t_philo *philo)
{
	long	start;
	long	remaining;

	start = get_mstime();
	while (1)
	{
		if (check_done(philo) == true)
			return ;
		remaining = duration_ms - (get_mstime() - start);
		if (remaining <= 0)
			break ;
		if (remaining > 1)
			usleep(500);
		else
			usleep(100);
	}
}
