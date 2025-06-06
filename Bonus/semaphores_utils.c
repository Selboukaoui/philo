/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:32:01 by selbouka          #+#    #+#             */
/*   Updated: 2025/06/04 16:48:13 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_semaphores(t_data *data)
{
	sem_unlink("/forks");
	sem_unlink("/write");
	sem_unlink("/meal");

	data->forks = sem_open("/forks", O_CREAT, 0644, data->n_philo);
	if (data->forks == SEM_FAILED)
		return (0);

	data->write_sem = sem_open("/write", O_CREAT, 0644, 1);
	if (data->write_sem == SEM_FAILED)
		return (0);

	data->meal_sem = sem_open("/meal", O_CREAT, 0644, 1);
	if (data->meal_sem == SEM_FAILED)
		return (0);

	return (1);
}

void	cleanup_semaphores(t_data *data)
{
	if (data->forks)
		sem_close(data->forks);
	if (data->write_sem)
		sem_close(data->write_sem);
	if (data->meal_sem)
		sem_close(data->meal_sem);

	sem_unlink("/forks");
	sem_unlink("/write");
	sem_unlink("/meal");
}

int	create_processes(t_data *data)
{
	int	i;

	data->pids = malloc(sizeof(pid_t) * data->n_philo);
	if (!data->pids)
		return (0);

	data->philos = malloc(sizeof(t_philo) * data->n_philo);
	if (!data->philos)
	{
		free(data->pids);
		return (0);
	}

	i = 0;
	while (i < data->n_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].start_time = data->start_time;
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].n_philo = data->n_philo;
		data->philos[i].t_die = data->t_die;
		data->philos[i].t_eat = data->t_eat;
		data->philos[i].t_sleep = data->t_sleep;
		data->philos[i].n_meals = data->n_meals;
		data->philos[i].forks = data->forks;
		data->philos[i].write_sem = data->write_sem;
		data->philos[i].meal_sem = data->meal_sem;

		data->pids[i] = fork();
		if (data->pids[i] == -1)
			return (0);
		if (data->pids[i] == 0)
			philosopher_routine(&data->philos[i]);
		i++;
	}
	return (1);
}