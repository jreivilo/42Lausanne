SRCS = srcs/atoi.c srcs/bsq.c srcs/condition.c srcs/matrix.c srcs/pre_instruction.c srcs/solver.c srcs/split.c srcs/square_management.c
OBJS = ${SRCS:.c=.o}
HEADERS = include/
NAME = bsq
RM = rm -f
CFLAGS = -Wall -Werror -Wextra
GCC = gcc

.c.o:	
			${GCC} ${FLAGS} -I ${HEADERS} -c $< -o ${<:.c=.o} 

${NAME}:	${OBJS}
			${GCC} -o ${NAME} ${OBJS} -I ${HEADERS}

all:		${NAME}

clean: 
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY: all clean fclean re