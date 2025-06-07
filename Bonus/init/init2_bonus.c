/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:53:30 by selbouka          #+#    #+#             */
/*   Updated: 2025/06/07 17:05:31 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	*monitor_all_full(void *arg)
{
	t_vars	*var;
	int		i, status;
	int		finished_processes;

	var = (t_vars *)arg;
	finished_processes = 0;
	
	while (finished_processes < var->n_philo)
	{
		i = 0;
		while (i < var->n_philo)
		{
			if (waitpid(var->p_id[i], &status, WNOHANG) > 0)
				finished_processes++;
			i++;
		}
		usleep(1000);
	}
	sem_post(var->die_sem);
	
	return (NULL);
}

int	create_processes(t_vars *var)
{
	int	i;

	i = 0;
	while (i < var->n_philo)
	{
		var->p_id[i] = fork();
		if (var->p_id[i] == 0)
		{
			routine(&var->philo[i]);
			exit(0);
		}
		else if (var->p_id[i] < 0)
		{
			printf("Error: Fork failed\n");
			return (0);
		}
		i++;
	}
	if (var->n_meals > 0)
	{
		if (pthread_create(&var->checker, NULL, monitor_all_full, var) != 0)
			return (0);
		pthread_detach(var->checker);
	}

	sem_wait(var->die_sem);

	i = 0;
	while (i < var->n_philo)
	{
		kill(var->p_id[i], SIGKILL);
		// waitpid(var->p_id[i], NULL, 0);
		i++;
	}

	return (1);
}
