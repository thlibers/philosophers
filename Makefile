# Name
NAME = philo

# Flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -I.
INCLUDES = -I./includes

# Paths
SRC_DIR = sources
OBJ_DIR = obj

# Srcs
SRCS =	$(SRC_DIR)/actions.c\
		$(SRC_DIR)/destroy.c\
		$(SRC_DIR)/init.c\
		$(SRC_DIR)/main.c\
		$(SRC_DIR)/monitor.c\
		$(SRC_DIR)/parsing.c\
		$(SRC_DIR)/routine.c\
		$(SRC_DIR)/utils.c\

# Obj
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

GREEN = \e[0;32m
RED = \e[0;31m
BLUE = \e[0;34m
RESET = \e[0m

all: $(NAME)

# Compilation program
$(NAME): $(OBJS)
	@echo "$(BLUE)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(RESET)"

# Compilation files obj
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean obj files
clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)✓ Object files cleaned!$(RESET)"

# Complete clean
fclean: clean
	@echo "$(RED)Cleaning executables...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)✓ Full clean completed!$(RESET)"

# Complete recompilation
re: fclean all

# Leaks
valgrind: $(NAME)
	@echo "$(BLUE)Checking for memory leaks with valgrind...$(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

# Rule .PHONY
.PHONY: all clean fclean re test leaks valgrind