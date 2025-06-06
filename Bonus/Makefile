CC = gcc

CFLAGS = -Wall -Wextra -Werror -pthread -g

NAME = philo_bonus

SRCS = main.c parsing_bonus.c utils_bonus.c \
       semaphores_utils.c init_bonus.c grb_collector.c \
       routine_bonus.c 

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re