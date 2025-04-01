CC := cc

# CFLAGS := -Werror -Wextra -Wall
CFLAGS := -Werror -Wextra -Wall -fsanitize=address -w

RM := rm -f

NAME := philo

MANDO := philo

OUTPUT := ${MANDO}/philo

SRCS := ${MANDO}/philo.c

OBJS := ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS} ${MANDO}/philo.h
	${CC} ${CFLAGS} ${OBJS} -o ${OUTPUT}

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

clean:
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${OUTPUT}

re: fclean all

.PHONY: all clean fclean re