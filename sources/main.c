/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 13:34:42 by thlibers          #+#    #+#             */
/*   Updated: 2026/03/16 14:53:38 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

int	main(int ac, char **av)
{
	long	*args;
	t_table	table;
	
	if (!parse(ac, av, &args))
		return (1);
	init_table(&table);
	// simulation
	// clean
	return (0);
}
