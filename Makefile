CC = cc

CFLAGS = -Wall -Wextra -Werror -I$(INCS) #-g3 -fsanitize=address

SRCS = pipex.c ft_strstr.c ft_split.c ft_strjoin.c error.c initializing.c commands.c

INCS = ./

NAME = pipex

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) Makefile pipex.h
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

.o: .c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean 
	rm -f $(NAME)

re: fclean all

.PHONY: all fclean clean re
