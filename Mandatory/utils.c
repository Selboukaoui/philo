/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:18:05 by selbouka          #+#    #+#             */
/*   Updated: 2025/03/19 03:38:45 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int clean_arg(char *arg)
{         
    while(*arg)
    {
        if (*arg == ' ' || *arg == '\t')
            arg++;
        else
            break ;
    }
    if (*arg == '+')
        arg++;
    while (*arg >= '0' && *arg <= '9')     
        arg++;
    while (*arg)
    {        
        if (*arg == ' ' || *arg == '\t')
            arg++;
         else   
            return (printf("Error\nArgument not valid!"), 0);
    }
    return (1);
}

int ft_atoi(char *arg)
{
    long    nbr;
    
    nbr = 0;
    if (!clean_arg(arg))
        return (0);
    while(*arg)
    {
        if (*arg == ' ' || *arg == '\t')
            arg++;
        else
            break ;
    }
    if (*arg == '+')
        arg++;
    while (*arg >= '0' && *arg <= '9')     
    {
        nbr = nbr * 10 + (*arg - '0');
        if (nbr > INT_MAX)
            return (printf("Error\nArgument out of range! "), 0);
        arg++;
    }
    return (nbr);
}


long get_time()
{
    struct timeval	tv;

    if (gettimeofday(&tv, NULL) == -1)
    {
        return(write(1, "gettimeofday failed\n", 21), 0);
        
    }
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}