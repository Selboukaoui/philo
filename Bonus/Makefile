CC = gcc

CFLAGS = -Wall -Wextra -Werror  
#-g -fsanitize=address -pthread

NAME = philo

SRCS = grb_collector.c init/init_bonus.c init/init2_bonus.c   main_bonus.c      parsing_bonus.c    routine_bonus.c     utils/utils_bonus.c utils/utils2_bonus.c

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