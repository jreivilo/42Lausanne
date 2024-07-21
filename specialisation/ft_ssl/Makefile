SRCS = src/main.c src/parsing_arg.c src/parsing_algo.c src/algo/md5.c src/print.c src/error.c src/algo/sha256.c
OBJS_DIR = obj
OBJS = $(addprefix $(OBJS_DIR)/,$(notdir $(SRCS:.c=.o)))
LIBFT_DIR = libft
HEADER = include
NAME = ft_ssl
RM = rm -f
CFLAGS = -Wall -Werror -Wextra
GCC = gcc -g
CC = gcc -g -lreadline

# FLAGS += -I$(HOME)/.brew/opt/readline/include
# READLINE += -L$(HOME)/.brew/opt/readline/lib

$(OBJS_DIR)/%.o: src/%.c
	$(GCC) $(CFLAGS) -I $(HEADER) -c $< -o $@

$(OBJS_DIR)/%.o: src/algo/%.c
	$(GCC) $(CFLAGS) -I $(HEADER) -c $< -o $@

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	cp $(LIBFT_DIR)/libft.a .
	$(CC) $(OBJS) $(CFLAGS) libft.a -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) libft.a
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
