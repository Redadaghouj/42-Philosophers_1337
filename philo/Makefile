CC := cc

CFLAGS := -Werror -Wextra -Wall
# CFLAGS := -Werror -Wextra -Wall -w -fsanitize=address -g
# CFLAGS := -Werror -Wextra -Wall -w -fsanitize=thread -g

RM := rm -f

NAME := philo

UTILS := utils

SRCS := philo.c parsing.c start_simulation.c stop_simulation.c life_cycle.c error_handlers.c \
		${UTILS}/ft_strlen.c ${UTILS}/ft_atoi.c ${UTILS}/ft_usleep.c\


OBJS := ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS} philo.h
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

clean:
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re