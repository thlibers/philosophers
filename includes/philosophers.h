/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:45:44 by nclavel           #+#    #+#             */
/*   Updated: 2026/03/16 14:52:13 by thlibers         ###   ########.fr       */
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

/* ========== parsing.c ========== */
bool	parse(int ac, char **av, long *arg);

/* ========== init.c ========== */
bool	init_table(t_table *table);

/* ========== destroy.c ========== */
void	destroy_table(t_table *table);

/* ========== actions.c ========== */

/* ========== routine.c ========== */

/* ========== monitor.c ========== */

/* ========== utils.c ========== */

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
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	int 				nb_meals; // -1 si non défini
	bool				is_dead;
	long				start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		death_mutex;
	t_philo				*philos;
}						t_table;

# include "mylibft/libft.h"
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

#endif
