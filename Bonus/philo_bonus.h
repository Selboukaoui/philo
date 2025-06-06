#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <limits.h>
# include <pthread.h>
# include <string.h>

# define DIED	1
# define FULL	0



typedef struct garbage_c
{
	void				*data;
	struct garbage_c	*next;
}	t_collect;



typedef struct s_philo
{
	int			id;
	int			meals_eaten;
	long long	last_meal_time;
	long long	start_time;
	int			n_philo;
	long long	t_die;
	long long	t_eat;
	long long	t_sleep;
	int			n_meals;
	sem_t		*forks;
	sem_t		*write_sem;
	sem_t		*meal_sem;
	pid_t		pid;
}	t_philo;

typedef struct s_data
{
	int			n_philo;
	long long	t_die;
	long long	t_eat;
	long long	t_sleep;
	int			n_meals;
	long long	start_time;
	pid_t		*pids;
	t_philo		*philos;
	sem_t		*forks;
	sem_t		*write_sem;
	sem_t		*meal_sem;
}	t_data;

// Function prototypes
int		parsing(char **av, t_data *data);
int		ft_atoi(char *arg);
long	get_time(void);
void	ft_sleep(long long time);
int		init_semaphores(t_data *data);
void	cleanup_semaphores(t_data *data);
void	philosopher_routine(t_philo *philo);
void	print_status(t_philo *philo, char *status);
int		create_processes(t_data *data);
void	*death_monitor(void *arg);

#endif