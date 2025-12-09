# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: your_login <your_login@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 00:00:00 by your_login       #+#    #+#              #
#    Updated: 2024/01/01 00:00:00 by your_login      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Library name
NAME = libgnl.a

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
BUFFER_SIZE = 42

# Source files
SRCS = get_next_line.c get_next_line_utils.c

# Object files
OBJS = $(SRCS:.c=.o)

# Header files
HEADERS = get_next_line.h

# Colors for output
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

# Default rule
all: $(NAME)

# Create the library
$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "$(GREEN)✓ $(NAME) created successfully!$(RESET)"

# Compile .c files to .o files
%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -D BUFFER_SIZE=$(BUFFER_SIZE) -c $< -o $@
	@echo "$(GREEN)✓ Compiled: $<$(RESET)"

# Clean object files
clean:
	@rm -f $(OBJS)
	@echo "$(RED)✗ Object files removed$(RESET)"

# Clean everything
fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)✗ $(NAME) removed$(RESET)"

# Rebuild everything
re: fclean all

# Bonus rule (if needed later)
bonus: all

# Phony targets
.PHONY: all clean fclean re bonus