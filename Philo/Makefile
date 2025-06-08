CC = gcc

CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address -pthread

NAME = philo

SRCS = grb_collector.c init/init.c init/init2.c   main.c      parsing.c    routine.c     utils/utils.c utils/utils2.c

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re