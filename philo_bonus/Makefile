CC := cc

# CFLAGS := -Werror -Wextra -Wall
#CFLAGS := -Werror -Wextra -Wall -w -fsanitize=address -g
CFLAGS := -Werror -Wextra -Wall -w -fsanitize=thread -g

RM := rm -f

NAME := philo_bonus

UTILS := utils

SRCS := philo_bonus.c parsing_bonus.c start_simulation_bonus.c stop_simulation_bonus.c life_cycle_bonus.c error_handlers_bonus.c \
		${UTILS}/ft_strlen_bonus.c ${UTILS}/ft_atoi_bonus.c ${UTILS}/ft_usleep_bonus.c\


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