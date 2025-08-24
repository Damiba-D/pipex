# Compiler and flags
CC		= gcc
CFLAGS	= -g -Wall -Wextra -Werror

# Project files
NAME	= pipex
SRCs	= pipex.c gen_utils.c arg_split.c cmdutils.c cmd1.c cmdmid.c cmd2.c
OBJs	= $(addprefix obj/, $(SRCs:.c=.o))

# Library paths
LIBFT_DIR	= libft
LIBFT_A		= $(LIBFT_DIR)/libft.a
PRINTF_A	= $(LIBFT_DIR)/ft_printf/libftprintf.a
GNL_A		= $(LIBFT_DIR)/get_next_line/get_next_line.a

# Final libraries to link
LIBS	= $(LIBFT_A) $(PRINTF_A) $(GNL_A)

# Includes
INCLUDES = -I$(LIBFT_DIR)

# Colors
GREEN	= \033[0;32m
YELLOW	= \033[1;33m
RED		= \033[0;31m
RESET	= \033[0m

# Rules
all: $(NAME)

$(NAME): $(OBJs)
	@echo "$(YELLOW)Compiling libft...$(RESET)"
	@make -C $(LIBFT_DIR) --no-print-directory
	@echo "$(YELLOW)Compiling pipex...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJs) $(LIBS) -o $(NAME)
	@echo "$(GREEN)Compilation done ✅$(RESET)"

# Object build rule
obj/%.o: %.c | obj
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ || \
	(echo "$(RED)Compilation failed ❌$(RESET)"; exit 1)

# Create obj directory if missing
obj:
	@mkdir -p obj

clean:
	@rm -rf obj
	@echo "$(YELLOW)Cleaned object files$(RESET)"

fclean: clean
	@make -C $(LIBFT_DIR) fclean --no-print-directory
	@rm -f $(NAME)
	@echo "$(YELLOW)Removed executable$(RESET)"

re: fclean all

.PHONY: all clean fclean re
