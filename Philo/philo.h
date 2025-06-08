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

#define DIED	2
#define FULL	3
#define LIFE	0

typedef struct vars
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	die;
	pthread_mutex_t	meals;

	pthread_t		checker;

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
	int			r_f;
	int			l_f;
	long		meals_eat;
	bool		is_eating;
	long		last_meal_eat;
	pthread_t	t_id;

	t_vars		*var;
}	t_philo;

typedef struct garbage_c
{
	void				*data;
	struct garbage_c	*next;
}	t_collect;

void	cleaning(t_vars *var, int j, int mutex);
int		parsing(char **av, t_vars *vr);
int		ft_atoi(char *arg);
int		data_init(t_vars *var);
void	*ft_malloc(size_t size, int mode);
long	get_time(void);
int		dead_flag(t_vars *var, int i, int status);
void	*routine(void *arg);
void	print(char *msg, t_philo *philo);
void	cleanthd(t_vars *var, int i);
void	ft_sleep(t_vars *var, long long sleep);
void	*monitoring(void *arg);
int		create_ph_threads(t_vars *var);
int		check_meals(t_vars *var);
