CC := cc

CFLAGS := -Werror -Wextra -Wall -fsanitize=thread -g

RM := rm -f

NAME := philo_bonus

SRCS := philo.c philo_utils.c parser.c start_simulation.c stop_simulation.c life_cycle.c \
		utils/ft_strlen.c utils/ft_atoi.c \


OBJS := ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS} philo_bonus.h
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

clean:
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re