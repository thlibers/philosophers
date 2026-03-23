/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:45:44 by nclavel           #+#    #+#             */
/*   Updated: 2026/03/23 15:43:47 by thlibers         ###   ########.fr       */
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
	pthread_mutex_t		*last_eat;
	pthread_mutex_t		*nb_eaten;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	int					nb_philos;
	int					done;
	long				start_time;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	int 				nb_meals; // -1 si non défini
	bool				is_dead;
	bool				shut_up;
	pthread_t			monitor_thread;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*shutup_mutex;
	pthread_mutex_t		*print_mutex;
	pthread_mutex_t		*done_mutex;
	pthread_mutex_t		*death_mutex;
	t_philo				*philos;
}						t_table;

/* ========== parsing.c ========== */
bool	parse(int ac, char **av, long *args);

/* ========== init.c ========== */
bool	init_table(t_table *table);

/* ========== destroy.c ========== */
void	destroy_table(t_table *table);

/* ========== actions.c ========== */
bool	ft_take_forks(t_philo *philo, pthread_mutex_t **first_fork, pthread_mutex_t **second_fork);
void	ft_eat(t_philo *philo);
void	ft_think(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_die(t_philo *philo);
// void	ft_drop_forks(t_philo *philo);

/* ========== routine.c ========== */
void	*routine(void *arg);

/* ========== monitor.c ========== */
void	*monitor_routine(void *arg);

/* ========== utils.c ========== */
long	ft_atol(const char *nptr);
void	safe_print(t_table *table, char *str, int nb);
long	get_mstime(void);
bool	check_die(t_table *table);
bool	check_done(t_philo *philo);
void	better_usleep(long duration_ms, t_philo *philo);

#endif
