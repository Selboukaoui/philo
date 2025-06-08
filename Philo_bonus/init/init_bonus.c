/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 07:26:21 by selbouka          #+#    #+#             */
/*   Updated: 2025/06/08 23:16:50 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	full_philo(t_vars *var)
{
	int	i;

	i = 0;
	while (i < var->n_philo)
	{
		var->philo[i].p_id = i + 1;
		sem_wait(var->meals_sem);
		var->philo[i].meals_eat = 0;
		var->philo[i].last_meal_eat = get_time();
		sem_post(var->meals_sem);
		var->philo[i].var = var;
		i++;
	}
}

int	init_semaphores(t_vars *var)
{
	sem_unlink("/write_sem");
	sem_unlink("/die_sem");
	sem_unlink("/meals_sem");
	sem_unlink("/forks_sem");
	(sem_unlink("/turn_sem"), sem_unlink("/full_sem"));
	var->write_sem = sem_open("/write_sem", O_CREAT | O_EXCL, 0644, 1);
	if (var->write_sem == SEM_FAILED)
		return (cleaning(var), 0);
	var->die_sem = sem_open("/die_sem", O_CREAT | O_EXCL, 0644, 0);
	if (var->die_sem == SEM_FAILED)
		return (cleaning(var), 0);
	var->meals_sem = sem_open("/meals_sem", O_CREAT | O_EXCL, 0644, 1);
	if (var->meals_sem == SEM_FAILED)
		return (cleaning(var), 0);
	var->forks_sem = sem_open("/forks_sem", O_CREAT | O_EXCL, \
		0644, var->n_philo);
	if (var->forks_sem == SEM_FAILED)
		return (cleaning(var), 0);
	var->turn_sem = sem_open("/turn_sem", O_CREAT | O_EXCL, 0644, 1);
	if (var->turn_sem == SEM_FAILED)
		return (cleaning(var), 0);
	var->full_sem = sem_open("/full_sem", O_CREAT | O_EXCL, 0644, 0);
	if (var->full_sem == SEM_FAILED)
		return (cleaning(var), 0);
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
		if (meals_tmp >= var->n_meals)
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
	var->pr_id = ft_malloc(sizeof(pid_t) * var->n_philo, 1);
	if (!var->pr_id)
		return (printf("Error: Memory allocation failed\n"), 0);
	if (!(init_semaphores(var)))
		return (printf("Error\nSemaphores init failed\n"), 0);
	var->full = false;
	var->start_t = get_time();
	if (var->start_t < 0)
		return (cleaning(var), 0);
	full_philo(var);
	create_processes(var);
	return (1);
}
