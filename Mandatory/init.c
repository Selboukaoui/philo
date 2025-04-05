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

void    full_philo(t_vars *var)
{
    int i;

    i = 0;
    while (i < var->n_philo)
    {
        var->philo[i].p_id = i + 1;
        pthread_mutex_lock(&var->meals);
        var->philo[i].meals_eat = 0;
        var->philo[i].last_meal_eat = get_time();
        pthread_mutex_unlock(&var->meals);
        var->philo[i].l_f = i;
        var->philo[i].r_f = (i + 1) % var->n_philo;
        var->philo[i].var = var;
        i++;
    }
}

int init_mutex(t_vars *var)
{
    int i = 0;

    if (pthread_mutex_init(&var->write, NULL) != 0)
    {
        return (0);
    }
    if (pthread_mutex_init(&var->die, NULL) != 0)
    {
        return (0);
    }
    if (pthread_mutex_init(&var->meals, NULL) != 0)
    {
        return (0);
    }
    while (i < var->n_philo)
    {
        if (pthread_mutex_init(&var->forks[i], NULL) != 0)
        {
            return (0); // I need to destroy all if anyone of them is fails.
        }
        i++;
    } 
    return (1);
}

int check_meals(t_vars *var)
{
    int meals_tmp;
    int philo_full;
    int i;

    philo_full = 0;
    i = 0;
    while (i < var->n_philo)
    {
        pthread_mutex_lock(var->meals);
        meals_tmp = var->philo->meals_eat;
        pthread_mutex_unlock(var->meals);
        if (meals_tmp == var->meals)
            philo_full++;
        i++;
    }
    return (philo_full == var->n_philo);
}

void    monitoring(t_vars *var)
{

    int i;
    long    time;

    while (1)
    {
        if (var->n_meals && check_meals(var))
            return (var->is_died = 3, 0);
        i = 0;
        while (i < var->n_philo)
        {
            pthread_mutex_lock(var->meals);
            time = var->philo[i].last_meal_eat;
            pthread_mutex_unlock(var->meals);
            if (get_time() - time > var->t_die)
                return(var->is_died = 2, 0);
            i++;
        }
        usleep(500);
        
    }
}

int data_init(t_vars *var)
{
    if (!(var->philo = ft_malloc(sizeof(t_philo) * var->n_philo, 1)))
        return (printf("Error\n Allocation failed\n"), 0);
    if (!(var->forks = ft_malloc(sizeof(pthread_mutex_t) * var->n_philo, 1)))
        return (printf("Error\n Allocation failed\n"), 0);
    if (!(init_mutex(var)))
        return (ft_malloc(0, 0), printf("Error\n Mutex init failed\n"), 0);
    if (!(var->start_t = get_time()))
        return (ft_malloc(0, 0), 0);
    dead_flag(var, 0);
    full_philo(var);
    if (pthread_create(&var->checker, NULL, monitoring, var) != 0)
        return (ft_malloc(0, 0), write(1, "Error\n Creat thread failed\n", 28), 0);
    


}

