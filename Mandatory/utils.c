/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:18:05 by selbouka          #+#    #+#             */
/*   Updated: 2025/06/04 13:40:44 by selbouka         ###   ########.fr       */
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


long    get_time()
{
    struct timeval	tv;

    if (gettimeofday(&tv, NULL) == -1)
    {
        return(write(1, "gettimeofday failed\n", 21), 0);
        
    }
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

int    dead_flag(t_vars *var, int i, int status)
{
    int tmp;

    tmp = 0;
    if (status == 0)
    {
        pthread_mutex_lock(&var->die);
        var->is_died = i;
        pthread_mutex_unlock(&var->die); 
    }
    else
    {
        pthread_mutex_lock(&var->die);
        tmp = var->is_died;
        pthread_mutex_unlock(&var->die); 
    }
    return (tmp);
}

void print(char *msg, t_philo *philo)
{
    if (dead_flag(philo->var, 0 , 69) != DIED)
    {
        pthread_mutex_lock(&philo->var->write);
        printf ("%lld\t%ld\t%s\n",(long long)(get_time() - philo->var->start_t), philo->p_id ,msg);
        pthread_mutex_unlock(&philo->var->write);
    }
}

void    ft_sleep(t_vars *var, long long sleep)
{
    long long   start;

    start = get_time();
    while (dead_flag(var, 0, 8) != DIED && (get_time() - start) < sleep)
        usleep (50);
}
