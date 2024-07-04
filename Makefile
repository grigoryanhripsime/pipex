CC = cc

CFLAGS = -Wall -Wextra -Werror -I$(INCS) -g3 -fsanitize=address

SRCS = pipex.c ft_split.c error.c initializing.c commands.c pipex_utils.c here_doc.c get_next_line.c get_next_line_utils.c

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
bonus: $(NAME)

.PHONY: all fclean clean re bonus
