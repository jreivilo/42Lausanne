SRCS = src/main.c src/ft_atoi.c src/init.c src/utils.c src/free.c src/monitor.c src/launcher.c
OBJS = ${SRCS:.c=.o}
HEADER = includes
NAME = philo
RM = rm -f
CFLAGS = -Wall -Werror -Wextra
GCC = gcc -g -pthread

.c.o:
			${GCC} ${CFLAGS} -I ${HEADER} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}	
			${GCC} ${CFLAGS} ${OBJS} -o ${NAME}

all: $(NAME)

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY: all clean fclean re