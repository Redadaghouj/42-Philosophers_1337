CC := cc

# CFLAGS := -Werror -Wextra -Wall
#CFLAGS := -Werror -Wextra -Wall -w -fsanitize=address -g
CFLAGS := -Werror -Wextra -Wall -w -fsanitize=thread -g

RM := rm -f

NAME := philo

UTILS := utils

ERR_HNDL := error_handlers

SRCS := philo.c ${ERR_HNDL}/print_error.c ${UTILS}/ft_strlen.c


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