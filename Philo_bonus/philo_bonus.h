/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 19:20:15 by selbouka          #+#    #+#             */
/*   Updated: 2025/06/06 19:20:15 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <limits.h>
#include <semaphore.h>
#include <signal.h>

typedef struct vars
{
	sem_t			*forks_sem;
	sem_t			*write_sem;
	sem_t			*die_sem;
	sem_t			*meals_sem;
	sem_t			*turn_sem;
	sem_t			*full_sem;

	bool			full;
	pid_t			*pr_id;
	int				*died;

	long long		start_t;
	long long		n_philo;
	long long		t_die;
	long long		is_died;
	long long		t_eat;
	long long		t_sleep;
	long long		n_meals;

	struct philo	*philo;

}	t_vars;

typedef struct philo
{
	long		p_id;
	long		meals_eat;
	bool		is_eating;
	long		last_meal_eat;
	pthread_t	death_monitor;

	t_vars		*var;
}	t_philo;

typedef struct garbage_c
{
	void				*data;
	struct garbage_c	*next;
}	t_collect;

void	cleaning(t_vars *var);
int		parsing(char **av, t_vars *vr);
int		ft_atoi(char *arg);
int		data_init(t_vars *var);
void	*ft_malloc(size_t size, int mode);
long	get_time(void);
void	*routine(void *arg);
void	print(char *msg, t_philo *philo);
void	ft_sleep(t_vars *var, long long sleep);
void	*monitoring(void *arg);
int		create_processes(t_vars *var);
int		check_meals(t_vars *var);
void	full_philo(t_vars *var);