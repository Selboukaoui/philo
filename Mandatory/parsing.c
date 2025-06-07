/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 21:48:02 by selbouka          #+#    #+#             */
/*   Updated: 2025/06/07 16:32:27 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_var(t_vars *vr, char **av)
{
	vr->n_philo = ft_atoi(av[1]);
	if (!vr->n_philo)
		return (0);
	vr->t_die = ft_atoi(av[2]);
	if (!vr->t_die)
		return (0);
	vr->t_eat = ft_atoi(av[3]);
	if (!vr->t_eat)
		return (0);
	vr->t_sleep = ft_atoi(av[4]);
	if (!vr->t_sleep)
		return (0);
	return (1);
}

int	parsing(char **av, t_vars *vr)
{
	if (!init_var(vr, av))
		return (0);
	if (vr->n_philo > 200 || vr->t_die < 60 || \
		vr->t_eat < 60 || vr->t_sleep < 60)
		return (printf("Error\nArgument not valid!"), 0);
	if (av[5])
	{
		vr->n_meals = ft_atoi(av[5]);
		if (!vr->n_meals)
			return (0);
	}
	else
		vr->n_meals = -99;
	return (1);
}
