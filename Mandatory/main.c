/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 21:47:57 by selbouka          #+#    #+#             */
/*   Updated: 2025/03/18 21:47:57 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_vars	var;

	if (ac != 5 && ac != 6)
		return (printf("Number of arguments is incorrect\n"), 0);
	if (!parsing(av, &var))
		return (1);
	if (!data_init(&var))
		return (1);
	cleaning (&var, var.n_philo + 3, false);
}
