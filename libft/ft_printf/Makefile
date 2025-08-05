# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/26 17:35:12 by ddamiba           #+#    #+#              #
#    Updated: 2025/06/09 14:19:53 by ddamiba          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = cc
CFLAGS = -g -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

SRC = \
	ft_printf.c ft_putchar.c ft_putnbr_base.c ft_putstr.c ft_putunsnbr_base.c ft_putptr.c ft_strlen.c

OBJ = $(SRC:.c=.o)

HEADER = ft_printf.h

# Default rule
make: all

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(BONUS_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re make
