#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/types.h>
#include <string.h>

// typedef 

typedef struct vars
{
	pthread_mutex_t *forks;
	long	fork_id;

	long n_philo;
	long t_die;
	long t_eat;
	long t_sleep;
	long t_think;
	long n_meals;

	// start
	bool	end; 
	struct philo	*philo;
}   t_vars;


typedef struct philo
{
	long p_id;
	t_vars *r_fork;
	t_vars *l_fork;
	long	n_meals;
	bool	full;
	long	last_meal_eat;
	pthread_t	t_id;

	t_vars	var;
} t_philo;



typedef struct garbage_c
{
	void				*data;
	struct garbage_c	*next;
}	t_collect;


int parsing(char **av, t_vars *vr);
int ft_atoi(char *arg);


int data_init(t_vars *var);

void	*ft_malloc(size_t size, int mode);