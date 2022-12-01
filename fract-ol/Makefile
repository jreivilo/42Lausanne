SRCS = src/drawing.c src/hook.c src/julia_utils.c src/main.c src/parse.c src/write.c src/check.c
OBJS = ${SRCS:.c=.o}
HEADER = includes
NAME = fractol
MLX_DIR = mlx
RM = rm -f
CFLAGS = -Wall -Werror -Wextra
GCC = gcc

.c.o:
			${GCC} ${CFLAGS} -I ${HEADER} -Imlx -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			@make -C ${MLX_DIR}
			cp ${MLX_DIR}/libmlx.dylib .			
			${GCC} ${CFLAGS} ${OBJS} -Lmlx -lmlx -framework OpenGL -framework AppKit -o ${NAME}

all: $(NAME)

clean:
			@make clean -C $(MLX_DIR)
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}
			${RM} libmlx.dylib

re:			fclean all

.PHONY: all clean fclean re