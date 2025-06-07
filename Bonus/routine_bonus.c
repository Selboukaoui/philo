/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:10:39 by selbouka          #+#    #+#             */
/*   Updated: 2025/06/07 17:07:29 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*death_monitor(void *arg)
{
	t_philo	*philo;
	long long	time_since_meal;

	philo = (t_philo *)arg;
	while (1)
	{
		time_since_meal = get_time() - philo->last_meal_eat;
		if (time_since_meal > philo->var->t_die)
		{
			sem_wait(philo->var->write_sem);
			printf("%lld %ld died\n", get_time() - philo->var->start_t, philo->p_id);
			sem_post(philo->var->die_sem);
			exit (1);
		}
		usleep(1000);
	}
	return (NULL);
}

void	take_forks(t_philo *philo)
{
	sem_wait(philo->var->forks_sem);
	print("has taken a fork", philo);
	sem_wait(philo->var->forks_sem);
	print("has taken a fork", philo);
}

void	eat(t_philo *philo)
{
	print("is eating", philo);
	philo->last_meal_eat = get_time();
	ft_sleep(philo->var, philo->var->t_eat);
	philo->meals_eat++;
}

void	put_forks(t_philo *philo)
{
	sem_post(philo->var->forks_sem);
	sem_post(philo->var->forks_sem);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	
	if (pthread_create(&philo->death_monitor, NULL, death_monitor, philo) != 0)
		return (NULL);
	pthread_detach(philo->death_monitor);
	
	if (philo->p_id % 2 == 0)
		usleep(10);
		// ft_sleep(philo->var, 20);

	while (1)
	{
		print("is thinking", philo);
		take_forks(philo);
		eat(philo);
		put_forks(philo);
		
		if (philo->var->n_meals > 0 && philo->meals_eat >= philo->var->n_meals)
			exit (1);
			
		print("is sleeping", philo);
		ft_sleep(philo->var, philo->var->t_sleep);
	}
	return (NULL);
}
