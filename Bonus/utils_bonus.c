/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:18:05 by selbouka          #+#    #+#             */
/*   Updated: 2025/06/04 16:35:48 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_sleep(long long time)
{
	long long	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(100);
}

int	clean_arg(char *arg)
{
	while (*arg)
	{
		if (*arg == ' ' || *arg == '\t')
			arg++;
		else
			break;
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
			return (printf("Error\nArgument not valid!\n"), 0);
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
			break;
	}
	if (*arg == '+')
		arg++;
	while (*arg >= '0' && *arg <= '9')
	{
		nbr = nbr * 10 + (*arg - '0');
		if (nbr > INT_MAX)
			return (printf("Error\nArgument out of range!\n"), 0);
		arg++;
	}
	return (nbr);
}