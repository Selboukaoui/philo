/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 19:10:11 by selbouka          #+#    #+#             */
/*   Updated: 2025/06/06 19:11:20 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_sleep(t_vars *var, long long sleep)
{
	long long	start;

	start = get_time();
	while (dead_flag(var, 0, 8) != DIED && (get_time() - start) < sleep)
		usleep (50);
}

int	clean_mutex(t_vars *var, int j)
{
	int	i;

	i = 0;
	if (j >= 1)
		pthread_mutex_destroy(&var->write);
	if (j >= 2)
		pthread_mutex_destroy(&var->die);
	if (j >= 3)
		pthread_mutex_destroy(&var->meals);
	j -= 3;
	while (i < j)
	{
		pthread_mutex_destroy(&var->forks[i]);
		i++;
	}
	if (j != var->n_philo)
		return (-666);
	return (0);
}

void	cleaning(t_vars *var, int j, bool mutex)
{
	int	i;

	if (mutex)
	{
		if (j < 0)
		{
			clean_mutex(var, var->n_philo + 3);
			ft_malloc(0, 0);
			return ;
		}
		if (clean_mutex(var, j) == -666)
		{
			ft_malloc(0, 0);
			return ;
		}
	}
	else
		clean_mutex(var, var->n_philo + 3);
	i = 0;
	while (i < j && i < var->n_philo)
	{
		pthread_detach(var->philo[i].t_id);
		i++;
	}
	ft_malloc(0, 0);
}
