/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:53:30 by selbouka          #+#    #+#             */
/*   Updated: 2025/06/08 23:00:11 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	join(t_vars *var)
{
	int	i;

	i = 0;
	while (i < var->n_philo)
	{
		if (pthread_join(var->philo[i].t_id, NULL) != 0)
			return (printf ("Error\nThread joining failed\n"), \
				cleaning(var, var->n_philo, false), 0);
		++i;
	}
	return (1);
}

int	create_ph_threads(t_vars *var)
{
	int	i;

	i = 0;
	var->start_t = get_time();
	if (var->start_t < 0)
		return (write(2, "Error\nGet time failed\n", 23), \
			cleaning(var, 0, 0), 0);
	while (i < var->n_philo)
	{
		if (pthread_create(&var->philo[i].t_id, NULL, \
			routine, &var->philo[i]) != 0)
			return (printf ("Error\nThread Creation failed\n"), \
				cleanthd(var, --i), 0);
		++i;
	}
	if (pthread_create(&var->checker, NULL, monitoring, var) != 0)
		return (write(1, "Error\n Creat thread failed\n", \
			28), cleanthd(var, i), 0);
	if (join(var) == 0)
		return (0);
	if (pthread_join(var->checker, NULL))
		return (printf ("Error\nThread joining failed\n"), \
			cleaning(var, var->n_philo, false), 0);
	return (1);
}

int	monitor_while(t_vars *var)
{
	long	time;
	bool	eat;
	int		i;

	i = 0;
	while (i < var->n_philo)
	{
		pthread_mutex_lock(&var->meals);
		time = get_time() - var->philo[i].last_meal_eat;
		eat = var->philo[i].is_eating;
		pthread_mutex_unlock(&var->meals);
		if (time > var->t_die && eat != true)
		{
			dead_flag(var, DIED, 0);
			pthread_mutex_lock(&var->write);
			printf ("%lld\t%ld\t%s\n", (long long)(get_time() \
			- var->start_t), var->philo[i].p_id, "died");
			pthread_mutex_unlock(&var->write);
			return (0);
		}
		i++;
	}
	return (1);
}

void	*monitoring(void *arg)
{
	t_vars	*var;

	var = (t_vars *)arg;
	while (69)
	{
		if (var->n_meals && check_meals(var))
		{
			dead_flag(var, FULL, 0);
			return (NULL);
		}
		if (!monitor_while(var))
			return (NULL);
		usleep (1000);
	}
}
