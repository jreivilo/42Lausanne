SRCS = src/main.c src/push.c src/reverse_rotate.c src/rotate.c src/swap.c src/small_sort.c \
src/medium_sort.c src/big_sort.c src/arg_check.c src/utils.c src/ft_atoi_l.c src/norminette.c src/sort.c src/opti.c src/free.c
OBJS = ${SRCS:.c=.o}
HEADER = includes
NAME = push_swap
LIBFT_DIR = libft
RM = rm -f
CFLAGS = -Wall -Werror -Wextra
GCC = gcc

.c.o:
			${GCC} ${CFLAGS} -I ${HEADER} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}	
			make -C ${LIBFT_DIR}
			cp ${LIBFT_DIR}/libft.a .
			${GCC} ${CFLAGS} ${OBJS} libft.a -o ${NAME}

all: $(NAME)

clean:
			${RM} ${OBJS}
			make clean -C ${LIBFT_DIR}

fclean:		clean
			${RM} ${NAME}
			${RM} libft.a
			make fclean -C ${LIBFT_DIR}

re:			fclean all

.PHONY: all clean fclean re