/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 21:48:02 by selbouka          #+#    #+#             */
/*   Updated: 2025/06/04 16:31:12 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int parsing(char **av, t_data *data)
{
    if (!(data->n_philo = ft_atoi(av[1])))
        return(0);
    if (!(data->t_die = ft_atoi(av[2])))
        return (0);
    if (!(data->t_eat = ft_atoi(av[3])))
        return (0);
    if (!(data->t_sleep = ft_atoi(av[4])))
        return (0);
    if (av[5])
    {
        if (!(data->n_meals = ft_atoi(av[5])))
            return (0);
    }
    else
        data->n_meals = -1;

    return (1);
}