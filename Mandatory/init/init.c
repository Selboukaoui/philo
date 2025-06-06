/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 07:26:21 by selbouka          #+#    #+#             */
/*   Updated: 2025/06/06 19:15:15 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	full_philo(t_vars *var)
{
	int	i;

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
		var->philo[i].is_eating = false;
		i++;
	}
}

int	init_mutex(t_vars *var)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&var->write, NULL) != 0)
		return (cleaning(var, 1, true), 0);
	if (pthread_mutex_init(&var->die, NULL) != 0)
		return (cleaning(var, 2, true), 0);
	if (pthread_mutex_init(&var->meals, NULL) != 0)
		return (cleaning(var, 3, true), 0);
	while (i < var->n_philo)
	{
		if (pthread_mutex_init(&var->forks[i], NULL) != 0)
			return (cleaning(var, i + 3, true), 0);
		i++;
	}
	return (1);
}

int	check_meals(t_vars *var)
{
	int	meals_tmp;
	int	philo_full;
	int	i;

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

int	data_init(t_vars *var)
{
	var->philo = ft_malloc(sizeof(t_philo) * var->n_philo, 1);
	if (!var->philo)
		return (printf("Error\nAllocation failed\n"), 0);
	var->forks = ft_malloc(sizeof(pthread_mutex_t) * var->n_philo, 1);
	if (!var->forks)
		return (printf("Error\nAllocation failed\n"), 0);
	if (!(init_mutex(var)))
		return (printf("Error\nMutex init failed\n"), 0);
	var->start_t = get_time();
	if (var->start_t < 0)
		return (cleaning(var, -99, true), 0);
	dead_flag(var, LIFE, 0);
	full_philo(var);
	create_ph_threads(var);
	return (1);
}
