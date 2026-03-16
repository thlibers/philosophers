/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 13:34:47 by thlibers          #+#    #+#             */
/*   Updated: 2026/03/16 14:57:14 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

static long	*check_args(int ac, char **av)
{
	int		i;
	int		j;
	long	*args;

	args = malloc(sizeof(long) * (ac - 1));
	if (!args)
		return (NULL);
	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] >= '0' && av[i][j] <= '9')
				return (NULL);
			j++;
		}
		args[i - 1] = ft_atol(av[i]);
		i++;
	}
	return (args);
}

bool	parse(int ac, char **av, long *args)
{
	int	i;

	i = 0;
	args = check_args(ac, av);
	if (!args)
		return (false);
	while (i < ac - 1)
	{
		if (!(args[i] < '0' || args[i] > INT_MAX))
			return (false);
		i++;
	}
	return (true);
}
