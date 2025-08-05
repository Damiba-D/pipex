# Compiler and flags
CC      = cc
CFLAGS  = -g -Wall -Wextra -Werror

# Files
NAME    = get_next_line.a
SRCS    = get_next_line.c get_next_line_utils.c
OBJS    = $(SRCS:.c=.o)
HEADER  = get_next_line.h

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
