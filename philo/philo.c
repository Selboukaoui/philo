#include "philo.h"

int main(int ac, char **av)
{
    pthread_t   vars;
    if (ac != 5 || ac != 6)
        return (printf("Number of arguments is incorrect\n"), 0);
    parsing(av);
}
