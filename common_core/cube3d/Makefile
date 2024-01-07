SRCS = srcs/main/main.c srcs/main/error.c\
		srcs/build/init.c \
		srcs/hooks/hook.c srcs/hooks/directions.c \
		srcs/parsing/add_protect.c srcs/parsing/check_map.c srcs/parsing/check_border.c srcs/parsing/check_border_utils.c srcs/parsing/parse_args.c srcs/parsing/parse_map.c srcs/parsing/parse_player.c srcs/parsing/parse_resolution.c srcs/parsing/parse_texture.c srcs/parsing/parse_texture_utils.c srcs/parsing/utils.c srcs/parsing/check_name.c \
		srcs/raycasting/raycasting.c srcs/raycasting/raycasting_utils.c srcs/raycasting/raycasting_utils2.c 
OBJS = ${SRCS:.c=.o}
LIBFT_DIR = libft
MLX_DIR = mlx
HEADER = includes
NAME = cub3D
RM = rm -f
CFLAGS = -Wall -Werror -Wextra -O2
GCC = gcc -g
CC = gcc -g -fsanitize=address -lreadline


FLAGS += -I$(HOME)/.brew/opt/readline/include
READLINE += -L$(HOME)/.brew/opt/readline/lib


.c.o:
			${GCC} ${CFLAGS} -I ${HEADER} -Imlx -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}	
				make -C ${LIBFT_DIR}
				cp ${LIBFT_DIR}/libft.a .
				@make -C ${MLX_DIR}
				cp ${MLX_DIR}/libmlx.dylib .
				${GCC} ${OBJS} ${CFLAGS} ${FLAGS} ${READLINE} -Lmlx -lmlx -framework OpenGL -framework AppKit libft.a -o ${NAME}

all: $(NAME)

clean:
			${RM} ${OBJS}
			make clean -C ${LIBFT_DIR}
			make clean -C ${MLX_DIR}

fclean:		clean
			${RM} ${NAME}
			${RM} libft.a
			${RM} libmlx.dylib
			make fclean -C ${LIBFT_DIR}

re:			fclean all

.PHONY: all clean fclean re