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

# Colors
GREEN   = \033[0;32m
YELLOW  = \033[0;33m
BLUE    = \033[0;34m
RESET   = \033[0m

# Default rule
all: submodules $(NAME)

$(NAME): $(OBJ)
	@echo "$(YELLOW)Compiling libft...$(RESET)"
	@$(AR) $(NAME) $(OBJ)
	@echo "$(GREEN)libft compilation done.$(RESET)"

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

# Build GNL and printf submodules
submodules:
	@echo "$(YELLOW)Compiling get_next_line...$(RESET)"
	@$(MAKE) -C $(GNL_DIR)
	@echo "$(YELLOW)Compiling ft_printf...$(RESET)"
	@$(MAKE) -C $(PRINTF_DIR)

# Cleaning rules
clean:
	@echo "$(BLUE)Cleaning libft objects...$(RESET)"
	@$(RM) $(OBJ)
	@$(MAKE) -C $(GNL_DIR) clean
	@$(MAKE) -C $(PRINTF_DIR) clean

fclean: clean
	@echo "$(BLUE)Removing libft binary...$(RESET)"
	@$(RM) $(NAME)
	@$(MAKE) -C $(GNL_DIR) fclean
	@$(MAKE) -C $(PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re submodules
