# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bboulmie <bboulmie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/07 18:12:13 by bboulmie          #+#    #+#              #
#    Updated: 2025/11/12 17:29:33 by bboulmie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            = cub3D

# ──────────────────────────────────────
# Tools
# ──────────────────────────────────────
CC              = cc
CFLAGS          = -Wall -Wextra -Werror -g -O0
INC             = -Iincludes -Ilibft/inc -IMLX42/include
LIBFT           = libft/libft.a
MLX42           = MLX42/build/libmlx42.a
DEPFLAGS        = -MMD -MP

# ──────────────────────────────────────
# Directories
# ──────────────────────────────────────
SRC_DIR         = src
RENDER_DIR      = $(SRC_DIR)/render
HOOKS_DIR       = $(SRC_DIR)/hooks
UTILS_DIR       = $(SRC_DIR)/utils
OBJ_DIR         = obj

# ──────────────────────────────────────
# Source files
# ──────────────────────────────────────
MAIN_SRC        =	$(SRC_DIR)/test_main.c

RENDER_SRC      =	$(RENDER_DIR)/init_mlx.c \
                	$(RENDER_DIR)/draw.c \
                	$(RENDER_DIR)/loop.c \
					$(RENDER_DIR)/raycaster.c \
					$(RENDER_DIR)/raycaster2.c \
                	$(RENDER_DIR)/test_map.c

HOOKS_SRC       =	$(HOOKS_DIR)/key_hook.c \
					$(HOOKS_DIR)/movement.c \
					$(HOOKS_DIR)/rotate.c

UTILS_SRC       =	$(UTILS_DIR)/error.c \
                	$(UTILS_DIR)/free.c \
                	$(UTILS_DIR)/rgb.c

SRC             =	$(MAIN_SRC) $(RENDER_SRC) $(HOOKS_SRC) $(UTILS_SRC)

# ──────────────────────────────────────
# Objects / Dependencies
# ──────────────────────────────────────
OBJ             = $(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(SRC)))
DEPS            = $(OBJ:.o=.d)

# ──────────────────────────────────────
# VPATH
# ──────────────────────────────────────
VPATH           = $(SRC_DIR):$(RENDER_DIR):$(HOOKS_DIR):$(UTILS_DIR)

# ──────────────────────────────────────
# Colors
# ──────────────────────────────────────
GREEN           = \033[1;32m
YELLOW          = \033[1;33m
BLUE            = \033[1;34m
RESET           = \033[0m

# ──────────────────────────────────────
# Rules
# ──────────────────────────────────────
all: $(NAME)

$(NAME): $(MLX42) $(LIBFT) $(OBJ)
	@echo "$(BLUE)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(INC) -o $@ $(OBJ) $(LIBFT) $(MLX42) \
		-lglfw -ldl -pthread -lm
	@echo "$(GREEN)Successfully built $(NAME)$(RESET)"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@echo "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INC) $(DEPFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@echo "$(BLUE)Building libft...$(RESET)"
	@$(MAKE) --no-print-directory -C libft > /dev/null

$(MLX42):
	@echo "$(BLUE)Building MLX42...$(RESET)"
	@cmake -B MLX42/build MLX42 > /dev/null
	@cmake --build MLX42/build -j4 > /dev/null

clean:
	@echo "$(YELLOW)Cleaning objects...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) --no-print-directory -C libft clean > /dev/null

fclean: clean
	@echo "$(YELLOW)Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) --no-print-directory -C libft fclean > /dev/null

re: fclean all

test: all
	@echo "$(GREEN)Running test map...$(RESET)"
	@./$(NAME)

norm:
	@norminette src/ includes/ libft/ | grep -v "OK" || true

# ──────────────────────────────────────
# Include generated dependencies
# ──────────────────────────────────────
-include $(DEPS)

.PHONY: all clean fclean re test norm