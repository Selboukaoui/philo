/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:53:30 by selbouka          #+#    #+#             */
/*   Updated: 2025/06/08 23:33:49 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

int	killing_check_full(t_vars *var)
{
	int	i;

	i = 0;
	if (var->n_meals > 0)
	{
		while (i < var->n_philo)
		{
			sem_wait(var->full_sem);
			i++;
		}
		sem_post(var->die_sem);
	}
	sem_wait(var->die_sem);
	i = 0;
	while (i < var->n_philo)
	{
		kill(var->pr_id[i], SIGKILL);
		i++;
	}
	return (1);
}

int	create_processes(t_vars *var)
{
	int	i;

	i = 0;
	while (i < var->n_philo)
	{
		var->pr_id[i] = fork();
		if (var->pr_id[i] == 0)
		{
			routine(&var->philo[i]);
			exit(0);
		}
		else if (var->pr_id[i] < 0)
		{
			printf("Error:\nFork failed");
			return (0);
		}
		i++;
	}
	if (killing_check_full(var) == 0)
		return (0);
	return (1);
}
