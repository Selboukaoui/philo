/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:10:39 by selbouka          #+#    #+#             */
/*   Updated: 2025/06/02 00:27:29 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void    take_fork(t_philo *philo)
{
    t_vars *var;

    var = philo->var;
    if (dead_flag(var, 0, 10) == 2)
        return ;
    if (philo->p_id % 2 == 0)
    {
        pthread_mutex_lock(&var->forks[philo->r_f]);
        print("has taken a fork", philo);

        pthread_mutex_lock(&var->forks[philo->l_f]);
        print("has taken a fork", philo); 
    }
    else
    {
        pthread_mutex_lock(&var->forks[philo->l_f]);
        print("has taken a fork", philo);

        pthread_mutex_lock(&var->forks[philo->r_f]);        
        print("has taken a fork", philo); 
    }
}

void    put_fork(t_philo *philo)
{
    t_vars  *var;

    var = philo->var;
    pthread_mutex_unlock(&var->forks[philo->r_f]);
    pthread_mutex_unlock(&var->forks[philo->l_f]);
}

void    eating(t_philo *philo)
{
    t_vars  *var;

    var = philo->var;
    pthread_mutex_lock(&var->meals);
    philo->last_meal_eat = get_time();
    philo->meals_eat++;
    pthread_mutex_unlock(&var->meals);
    usleep(var->t_eat * 1000);
}

void    routine_loop(t_philo *philo)
{
    t_vars  *var;
    int status;

    var = philo->var;
    while (dead_flag(var, 0, 7) == LIFE)
    {
        
        print("is thinking", philo);
        take_fork(philo);
        print("is eating", philo);
        eating(philo);
        put_fork(philo);
        print("is sleeping", philo);
        usleep(var->t_sleep * 1000);
        status = dead_flag(var, 0, 8);
        if (status != LIFE)
        {
            if (status == DIED)
                print("died", philo);
            break ;
        }
    }
}

void    *routine(void *arg)
{
    t_philo *philo;
    t_vars  *var;
    
    philo = (t_philo *)arg;
    var = philo->var;
    if (var->n_philo == 1)
    {
        print("is thinking", philo);
        print("has taken a fork", philo);
        usleep(var->t_sleep * 1000);
        print("died", philo);
        dead_flag(var, DIED, 0);
        return (NULL);
    }
    if (philo->p_id % 2 == 0)
        usleep((var->t_die) / 2);
    routine_loop(philo);
    return (NULL);
}
