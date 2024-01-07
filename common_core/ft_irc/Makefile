NAME		=	ircserv

SDIR		=	srcs

SRCS		= main.cpp core/server.cpp core/client.cpp core/channel.cpp\
				utils/utils.cpp utils/parser.cpp \
				commands/nick.cpp \
				commands/user.cpp \
				commands/join.cpp \
				commands/privmsg.cpp \
				commands/pass.cpp \
				commands/kick.cpp \
				commands/topic.cpp \
				commands/invite.cpp \
				commands/mode.cpp \

IDIR		=	includes

ODIR		=	objs

OBJS		=	$(addprefix $(ODIR)/,$(SRCS:.cpp=.o))

RM			=	rm -rf

CXX			=	c++

# CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98 -g -fsanitize=address
CXXFLAGS	=	-Wall -Wextra -std=c++98

$(ODIR)/%.o	:	$(SDIR)/%.cpp $(INCS)
			@mkdir -p $(@D)
			$(CXX) $(CXXFLAGS) -c $< -o $@

$(NAME)		:	$(OBJS)
			$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

all			:	$(NAME)

clean		:
			$(RM) $(ODIR)

fclean		:	clean
			$(RM) $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re
