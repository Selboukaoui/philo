/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 07:26:21 by selbouka          #+#    #+#             */
/*   Updated: 2025/03/19 07:57:31 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int data_init(t_vars *var)
{
    var->end = false;
    if (!(var->philo = ft_malloc(sizeof(t_philo) * var->n_philo, 1)))
        return (printf("Error\n Allocation failed\n"), 0);
    if (!(var->forks = ft_malloc(sizeof(pthread_mutex_t) * var->n_philo, 1)))
        return (printf("Error\n Allocation failed\n"), 0);
    
    
}