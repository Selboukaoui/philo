/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 21:48:02 by selbouka          #+#    #+#             */
/*   Updated: 2025/03/19 07:08:35 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int parsing(char **av, t_vars *vr)
{
    if (!(vr->n_philo = ft_atoi(av[1])))
        return(0);
    if (!(vr->t_die = ft_atoi(av[2])))
        return (0);
    if (!(vr->t_eat = ft_atoi(av[3])))
        return (0);
    if (!(vr->t_sleep = ft_atoi(av[4])))
        return (0);
    if (av[5])
        if (!(vr->n_meals = ft_atoi(av[5])))
            return (0);
    else
        vr->n_meals = -99;



    // printf ("%d\n",vr->n_philo);
    return (1);
}


