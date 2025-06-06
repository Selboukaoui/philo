/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 07:26:21 by selbouka          #+#    #+#             */
/*   Updated: 2025/06/04 16:47:22 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_status(t_philo *philo, char *status)
{
	long long	current_time;

	sem_wait(philo->write_sem);
	current_time = get_time() - philo->start_time;
	printf("%lld %d %s\n", current_time, philo->id, status);
	sem_post(philo->write_sem);
}

void	take_forks(t_philo *philo)
{
	sem_wait(philo->forks);
	print_status(philo, "has taken a fork");
	sem_wait(philo->forks);
	print_status(philo, "has taken a fork");
}

void	eat(t_philo *philo)
{
	print_status(philo, "is eating");
	
	sem_wait(philo->meal_sem);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	sem_post(philo->meal_sem);
	
	ft_sleep(philo->t_eat);
	
	sem_post(philo->forks);
	sem_post(philo->forks);
}

void	*death_monitor(void *arg)
{
	t_philo	*philo;
	long long	time_since_meal;

	philo = (t_philo *)arg;
	while (1)
	{
		usleep(1000);
		sem_wait(philo->meal_sem);
		time_since_meal = get_time() - philo->last_meal_time;
		if (time_since_meal >= philo->t_die)
		{
			sem_post(philo->meal_sem);
			print_status(philo, "died");
			exit(DIED);
		}
		if (philo->n_meals > 0 && philo->meals_eaten >= philo->n_meals)
		{
			sem_post(philo->meal_sem);
			exit(FULL);
		}
		sem_post(philo->meal_sem);
	}
	return (NULL);
}

void	philosopher_routine(t_philo *philo)
{
	pthread_t	monitor_thread;

	if (pthread_create(&monitor_thread, NULL, death_monitor, philo) != 0)
		exit(1);
	pthread_detach(monitor_thread);
	
	if (philo->n_philo == 1)
	{
		sem_wait(philo->forks);
		print_status(philo, "has taken a fork");
		ft_sleep(philo->t_die);
		print_status(philo, "died");
		exit(DIED);
	}

	if (philo->id % 2 == 0)
		ft_sleep(philo->t_eat / 2);

	while (1)
	{
		print_status(philo, "is thinking");
		take_forks(philo);
		eat(philo);
		print_status(philo, "is sleeping");
		ft_sleep(philo->t_sleep);
	}
}