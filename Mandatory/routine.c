/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:10:39 by selbouka          #+#    #+#             */
/*   Updated: 2025/06/03 20:02:51 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


// void take_fork(t_philo *philo)
// {
//     t_vars *var = philo->var;
//     if (dead_flag(var, 0, 10) == DIED)
//         return;

//     int first, second;
    
//     // First philosopher takes left fork first
//     if (philo->p_id == 1) {
//         first = philo->l_f;
//         second = philo->r_f;
//     }
//     // Last philosopher takes right fork first
//     else if (philo->p_id == var->n_philo) {
//         first = philo->r_f;
//         second = philo->l_f;
//     }
//     // Others take lower-numbered fork first
//     else {
//         first = (philo->l_f < philo->r_f) ? philo->l_f : philo->r_f;
//         second = (philo->l_f < philo->r_f) ? philo->r_f : philo->l_f;
//     }
    
//     pthread_mutex_lock(&var->forks[first]);
//     print("has taken a fork", philo);
    
//     pthread_mutex_lock(&var->forks[second]);
//     print("has taken a fork", philo);
// }

void    take_fork(t_philo *philo)
{
    t_vars *var;

    var = philo->var;
    if (dead_flag(var, 0, 10) == DIED)
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
    philo->is_eating = true; //
    pthread_mutex_unlock(&var->meals);
    
    ft_sleep(var, var->t_eat * 1000);

    pthread_mutex_lock(&var->meals);
    philo->is_eating = false;
    pthread_mutex_unlock(&var->meals);
}

void    routine_loop(t_philo *philo)
{
    t_vars  *var;
    int status;

    var = philo->var;
    while (dead_flag(var, 0, 7) == LIFE)
    {
        
        take_fork(philo);
        print("is eating", philo);
        eating(philo);
        put_fork(philo);
        print("is sleeping", philo);
        print("is thinking", philo);
        ft_sleep(var, var->t_sleep * 1000);
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
        print("has taken a fork", philo);
        ft_sleep(var, var->t_sleep * 1000);
        // print("is thinking", philo);
        print("died", philo);
        dead_flag(var, DIED, 0);
        return (NULL);
    }
    if (philo->p_id % 2 == 0)
        ft_sleep(var, var->t_die / 2);
    routine_loop(philo);
    return (NULL);
}
