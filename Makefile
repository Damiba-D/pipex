# Compiler and flags
CC		= gcc
CFLAGS	= -g -Wall -Wextra -Werror

# Project files
NAME	= pipex
SRC		= pipex.c

# Library paths
LIBFT_DIR	= libft
LIBFT_A		= $(LIBFT_DIR)/libft.a
PRINTF_A	= $(LIBFT_DIR)/ft_printf/libftprintf.a
GNL_A		= $(LIBFT_DIR)/get_next_line/get_next_line.a

# Final libraries to link
LIBS	= $(LIBFT_A) $(PRINTF_A) $(GNL_A)

# Includes (optional, in case headers are needed)
INCLUDES = -I$(LIBFT_DIR)

# Rules
all: $(NAME)

$(NAME): $(SRC)
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC) $(LIBS) -o $(NAME)

clean:
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
