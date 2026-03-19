/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:45:44 by nclavel           #+#    #+#             */
/*   Updated: 2026/03/19 12:38:15 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_table	t_table;

typedef struct s_philo
{
	int					id;
	int					meals_eaten;
	long				last_meal_time;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	int					nb_philos;
	long				start_time;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	int 				nb_meals; // -1 si non défini
	bool				is_dead;
	bool				*shut_up;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*print_mutex;
	pthread_mutex_t		*death_mutex;
	t_philo				*philos;
}						t_table;

/* ========== parsing.c ========== */
bool	parse(int ac, char **av, long *arg);

/* ========== init.c ========== */
bool	init_table(t_table *table);

/* ========== destroy.c ========== */
void	destroy_table(t_table *table);

/* ========== actions.c ========== */

/* ========== routine.c ========== */

/* ========== monitor.c ========== */
void	*monitor_routine(void *arg);

/* ========== utils.c ========== */
long	ft_atol(const char *nptr);
void	safe_print(t_table *table, char *str, int nb);
int		get_mstime(void);
bool	check_die(t_table *table);

#endif
