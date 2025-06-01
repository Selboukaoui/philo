/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:10:39 by selbouka          #+#    #+#             */
/*   Updated: 2025/06/01 20:26:40 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void    take_fork(t_philo *philo)
{
    t_vars *var;

    var = philo->var;
    pthread_mutex_lock(&var->forks[philo->r_f]);
    print("has taken a fork", var);

    pthread_mutex_lock(&var->forks[philo->l_f]);
    print("has taken a fork", var);
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
    var->philo->last_meal_eat = get_time();
    var->philo->meals_eat++;
    pthread_mutex_unlock(&var->meals);
    usleep(var->t_eat);
}

void    routine_loop(t_philo *philo)
{
    static int i;
    t_vars  *var;

    var = philo->var;
    while (dead_flag(var, 0, 7) == LIFE)
    {
        
        print("is thinking", var);
        take_fork(var->philo);
        print("is eating", var);
        eating(var->philo);
        put_fork(var->philo);
        print("is sleeping", var);
        usleep(var->t_sleep);
        if (dead_flag(var, 0, 8) != 0)
        {
            if (dead_flag(var, 0, 9) == DIED)
                print("died", var);
            break ;
        }
        sleep(1);
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
        print("is thinking", var);
        print("has taken a fork", var);
        usleep(var->t_sleep);
        print("died", var);
        dead_flag(var, DIED, 0);
        return (NULL);
    }
    if (var->philo->p_id % 2 == 0)
        usleep(var->t_die / 2);
    routine_loop(philo);
    return (NULL);
}
