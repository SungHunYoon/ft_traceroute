CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = ./traceroute.c ./parse.c ./error.c ./ft_utils.c ./utils.c
OBJS = $(SRCS:.c=.o)
NAME = ft_traceroute

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lm

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : 
	make fclean
	make all

.PHONY : all clean fclean re
