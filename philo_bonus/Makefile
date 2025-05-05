CC := cc

CFLAGS := -Werror -Wextra -Wall

RM := rm -f

NAME := philo_bonus

SRCS := philo_bonus.c cleanup_bonus.c philo_utils_bonus.c parser_bonus.c start_simulation_bonus.c stop_simulation_bonus.c life_cycle_bonus.c \
		utils/ft_strlen_bonus.c utils/ft_atoi_bonus.c utils/ft_strcmp_bonus.c \


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