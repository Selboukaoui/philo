/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 19:10:11 by selbouka          #+#    #+#             */
/*   Updated: 2025/06/07 16:46:48 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	ft_sleep(t_vars *var, long long sleep)
{
	long long	start;

	(void)var;
	start = get_time();
	while ((get_time() - start) < sleep)
		usleep (50);
	// dead_flag(var, 0, 8) != DIED && 
}

void	cleaning(t_vars *var)
{
	if (var->write_sem != SEM_FAILED)
	{
		sem_close(var->write_sem);
		sem_unlink("/write_sem");
	}
	if (var->die_sem != SEM_FAILED)
	{
		sem_close(var->die_sem);
		sem_unlink("/die_sem");
	}
	if (var->forks_sem != SEM_FAILED)
	{
		sem_close(var->forks_sem);
		sem_unlink("/forks_sem");
	}
	ft_malloc(0, 0);
}


