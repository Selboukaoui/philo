#include "philo.h"

void    dead_flag(t_vars *var, int i)
{
    pthread_mutex_lock(&var->die);
    pthread_mutex_unlock(&var->die);
}