src = grb_collector.c  init.c  main.c  parsing.c  utils.c routine.c

# all: philo

philo:
	cc -fsanitize=thread -g $(src) -o philo

fclean:
	rm philo

re:
	rm philo
	make