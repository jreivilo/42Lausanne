NAME = pipex
SRCS = pipex.c \
		free.c \
		utils.c

FLAGS= -Wall -Wextra -Werror
rm = rm -f
CC = gcc

all : $(NAME)

$(NAME) : $(LIBFT)
	@cp ./libft/libft.a .
	@$(CC) $(FLAGS) $(SRCS) libft.a -o $(NAME)
	
$(LIBFT) :
	@$(MAKE) -C ./libft
	
clean :
	@$(rm) libft.a
	@$(MAKE) -C ./libft clean
	
fclean : clean
	@$(rm) $(NAME)

re: fclean all

.PHONY: all clean fclean re