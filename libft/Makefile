# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/26 17:35:12 by ddamiba           #+#    #+#              #
#    Updated: 2025/07/31 14:17:18 by ddamiba          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Library Name
NAME = libft.a

# Compiler & Tools
CC = cc
CFLAGS = -g -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

# Submodules
GNL_DIR = get_next_line
PRINTF_DIR = ft_printf

# Source Files
SRC = ${wildcard *.c}
	
OBJ = $(SRC:.c=.o)
HEADER = libft.h

# Default rule
all: submodules $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ $(LFLAGS)

# Build GNL and printf submodules
submodules:
	@$(MAKE) -C $(GNL_DIR)
	@$(MAKE) -C $(PRINTF_DIR)

# Cleaning rules
clean:
	$(RM) $(OBJ)
	@$(MAKE) -C $(GNL_DIR) clean
	@$(MAKE) -C $(PRINTF_DIR) clean

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C $(GNL_DIR) fclean
	@$(MAKE) -C $(PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re submodules

