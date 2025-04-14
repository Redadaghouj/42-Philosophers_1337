CC := cc

# CFLAGS := -Werror -Wextra -Wall
CFLAGS := -Werror -Wextra -Wall -fsanitize=address -w

RM := rm -f

NAME := philo

SRCS := philo.c

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