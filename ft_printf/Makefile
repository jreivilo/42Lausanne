SRCS = ft_printf.c  ft_printf_utils_c.c ft_printf_utils_x_xx.c ft_printf_utils_u.c \
ft_printf_utils_p.c ft_printf_utils_s.c ft_printf_utils_i_d.c
OBJS = ${SRCS:.c=.o}
HEADER = ft_printf.h
NAME = libftprintf.a
LIBFT_DIR = libft
RM = rm -f
CFLAGS = -Wall -Werror -Wextra
ARRC = ar rc
GCC = gcc

.c.o:
			${GCC} ${CFLAGS} -I ${HEADER} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			@make -C ${LIBFT_DIR}
			cp ${LIBFT_DIR}/libft.a ${NAME}
			${ARRC} ${NAME} ${OBJS}

all:		${NAME}

clean:
			@make clean -C $(LIBFT_DIR)
			${RM} ${OBJS}

fclean:		clean
			@make fclean -C $(LIBFT_DIR)
			${RM} ${NAME}

re:			fclean all

.PHONY: all clean fclean re
