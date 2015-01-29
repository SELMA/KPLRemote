CC		= g++

RM		= rm -rf

PATH_SOURCES	= ./sources

CPPFLAGS	+= -Wextra -Wall -Werror -g
CPPFLAGS	+= -ansi -pedantic
CPPFLAGS	+= -I./includes/

LDFLAGS		+= $(CPPFLAGS) -lws2_32 -lgdi32

CLIENT		= KPLRemote_client

VICTIME		= KPLRemote_victime

SRCS_VICTIME	= $(PATH_SOURCES)/main.cpp	    \
		  $(PATH_SOURCES)/MyIrc.cpp	    \
		  $(PATH_SOURCES)/Key.cpp	    \
		  $(PATH_SOURCES)/MySocket.cpp

OBJS_VICTIME	= $(SRCS_VICTIME:.cpp=.o)


$(VICTIME):	$(OBJS_VICTIME)
		$(CC) $(OBJS_VICTIME) -o $(VICTIME) $(LDFLAGS)

all:		$(VICTIME)

clean:
		$(RM) $(OBJS_VICTIME)

fclean:		clean
		$(RM) $(VICTIME).exe

re:		fclean all

.PHONY:		all clean fclean re
