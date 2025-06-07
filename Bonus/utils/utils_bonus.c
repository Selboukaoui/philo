/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:18:05 by selbouka          #+#    #+#             */
/*   Updated: 2025/06/07 16:35:25 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

int	clean_arg(char *arg)
{
	while (*arg)
	{
		if (*arg == ' ' || *arg == '\t')
			arg++;
		else
			break ;
	}
	if (*arg == '+')
		arg++;
	while (*arg >= '0' && *arg <= '9')
		arg++;
	while (*arg)
	{
		if (*arg == ' ' || *arg == '\t')
			arg++;
		else
			return (printf("Error\nArgument not valid!"), 0);
	}
	return (1);
}

int	ft_atoi(char *arg)
{
	long	nbr;

	nbr = 0;
	if (!clean_arg(arg))
		return (0);
	while (*arg)
	{
		if (*arg == ' ' || *arg == '\t')
			arg++;
		else
			break ;
	}
	if (*arg == '+')
		arg++;
	while (*arg >= '0' && *arg <= '9')
	{
		nbr = nbr * 10 + (*arg - '0');
		if (nbr > INT_MAX)
			return (printf("Error\nArgument out of range! "), 0);
		arg++;
	}
	return (nbr);
}

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		return (write(1, "gettimeofday failed\n", 21), -1);
	}
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

// int	dead_flag(t_vars *var, int i, int status)
// {
// 	int	tmp;

// 	tmp = 0;
// 	if (status == 0)
// 	{
// 		// sem_wait(var->death_event_sem);
// 		var->is_died = i;
// 		// sem_post(var->death_event_sem);
// 	}
// 	else
// 	{
// 		// sem_wait(var->death_event_sem);
// 		tmp = var->is_died;
// 		// sem_post(var->death_event_sem);
// 	}
// 	return (tmp);
// }

void print(char *msg, t_philo *philo)
{
    sem_wait(philo->var->write_sem);
    long current = get_time() - philo->var->start_t;
    printf("%ld\t%ld\t%s\n", current, philo->p_id, msg);
    sem_post(philo->var->write_sem);
}







// void	print(char *msg, t_philo *philo)
// {
// 	// pthread_mutex_lock(&philo->var->write);
// 	sem_wait(philo->var->write_sem);
// 	// if (dead_flag(philo->var, 0, 69) != DIED)
// 	// {
// 		printf ("%lld\t%ld\t%s\n", (long long)(get_time() \
// 		- philo->var->start_t), philo->p_id, msg);
// 	// }
// 	sem_post(philo->var->write_sem);
// 	// pthread_mutex_unlock(&philo->var->write);
// }
