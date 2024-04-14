NAME		=	ft_kalman

SDIR		=	src

SRCS		= main.cpp parsing.cpp utils.cpp rotation.cpp matrix.cpp

IDIR		=	includes

ODIR		=	obj

OBJS		=	$(addprefix $(ODIR)/,$(SRCS:.cpp=.o))

RM			=	rm -rf

CXX			=	c++

LIBS		= eigen

# CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98 -g -fsanitize=address
CXXFLAGS	=	

$(ODIR)/%.o	:	$(SDIR)/%.cpp $(INCS)
			@mkdir -p $(@D)
			$(CXX) -I ${LIBS} $(CXXFLAGS) -c $< -o $@

$(NAME)		:	$(OBJS)
			$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

all			:	$(NAME)

clean		:
			$(RM) $(ODIR)

fclean		:	clean
			$(RM) $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re