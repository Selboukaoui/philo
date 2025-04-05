// #include <pthread.h>
// #include <stdio.h>
// #include <unistd.h>
// #include <limits.h>
// # include <sys/time.h>
// #include <sys/types.h>
// #include <string.h>

#include <stdlib.h>
#include <stdbool.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef struct vars
{
	pthread_mutex_t *forks;
	pthread_mutex_t	write;
	pthread_mutex_t	die;
	pthread_mutex_t	meals;
	
	struct philo	*philo;
	pthread_t	checker;

	long	fork_id;
	long	start_t;
	long n_philo;
	long t_die;
	long is_died;
	long t_eat;
	long t_sleep;
	long t_think;
	long n_meals;

	// start
	// bool	end; 
}   t_vars;


typedef struct philo
{
	long p_id;
	int	r_f;
	int	l_f;
	long	meals_eat;
	bool	full;
	long	last_meal_eat;
	pthread_t	t_id;

	t_vars	*var;
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

long get_time(void);
void    dead_flag(t_vars *var, int i);