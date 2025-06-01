/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 07:26:21 by selbouka          #+#    #+#             */
/*   Updated: 2025/06/02 00:08:53 by selbouka         ###   ########.fr       */
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
        meals_tmp = var->philo[i].meals_eat;
        
        if (meals_tmp == var->n_meals)
            philo_full++;
        i++;
    }
    return (philo_full == var->n_philo);
}

void   *monitoring(void *arg)
{
    int i;
    long    time;
    t_vars *var;

    var = (t_vars *)arg;
    while (1)
    {
        pthread_mutex_lock(&var->meals);
        if (var->n_meals && check_meals(var))
        {
            dead_flag(var, FULL, 0);
            pthread_mutex_unlock(&var->meals);
            return (NULL);
        }
        pthread_mutex_unlock(&var->meals);
        i = 0;
        while (i < var->n_philo)
        {
            pthread_mutex_lock(&var->meals);
            time = var->philo[i].last_meal_eat;
            pthread_mutex_unlock(&var->meals);
            if (get_time() - time > var->t_die)
            {
                print ("died", &var->philo[i]);
                dead_flag(var, DIED, 0);
                return (NULL);
            }
            i++;// is eating
        }
        usleep(500);
    }
}

int    create_ph_threads(t_vars *var)
{
    int i = 0;

    var->start_t = get_time();
    while (i < var->n_philo)
    {
        if (pthread_create(&var->philo[i].t_id, NULL, routine, &var->philo[i]) != 0)
        {
            return (printf ("Error\nThread Creation failed\n"), i); // clean
        }
        ++i;
    }
    if (pthread_create(&var->checker, NULL, monitoring, var) != 0)
        return (ft_malloc(0, 0), write(1, "Error\n Creat thread failed\n", 28), 0);
    i = 0;
    while (i < var->n_philo)
    {
        if (pthread_join(var->philo[i].t_id, NULL) != 0)
            return (printf ("Error\nThread joining failed\n"), i);
        ++i;
    }
    if (pthread_join(var->checker, NULL))
        return (ft_malloc(0, 0), printf("Error\nThread joining failed\n"));
    return (0);
}

int data_init(t_vars *var)
{
    if (!(var->philo = ft_malloc(sizeof(t_philo) * var->n_philo, 1)))
        return (printf("Error\nAllocation failed\n"), 0);
    if (!(var->forks = ft_malloc(sizeof(pthread_mutex_t) * var->n_philo, 1)))
        return (printf("Error\nAllocation failed\n"), 0);
    if (!(init_mutex(var)))
        return (ft_malloc(0, 0), printf("Error\nMutex init failed\n"), 0);

    if (!(var->start_t = get_time()))
        return (ft_malloc(0, 0), 0);
    dead_flag(var, LIFE, 0);
    full_philo(var);
    create_ph_threads(var);

    return (1);
}

