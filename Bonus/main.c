/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 21:47:57 by selbouka          #+#    #+#             */
/*   Updated: 2025/03/18 21:47:57 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_all_processes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		kill(data->pids[i], SIGKILL);
		i++;
	}
}

void	wait_for_processes(t_data *data)
{
	int	i;
	int	status;
	int	full_count;

	i = 0;
	full_count = 0;
	while (i < data->n_philo)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == DIED)
			{
				kill_all_processes(data);
				return ;
			}
			else if (WEXITSTATUS(status) == FULL)
				full_count++;
		}
		i++;
	}
	if (full_count == data->n_philo)
		printf("All philosophers have eaten %d meals\n", data->n_meals);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		return (printf("Usage: %s number time_die time_eat time_sleep [meals]\n", av[0]), 1);
	memset(&data, 0, sizeof(t_data));
	if (!parsing(av, &data))
		return (1);
	if (!init_semaphores(&data))
		return (1);
	data.start_time = get_time();
	if (!create_processes(&data))
	{
		cleanup_semaphores(&data);
		return (1);
	}
	wait_for_processes(&data);
	cleanup_semaphores(&data);
	free(data.pids);
	free(data.philos);
	return (0);
}