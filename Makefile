# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 15:09:24 by igilani           #+#    #+#              #
#    Updated: 2025/07/25 17:46:11 by igilani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ========================================================================== #
#                                 CONFIGURATION                             #
# ========================================================================== #

# Comportamento predefinito
.DEFAULT_GOAL := silent

# Compilatore e flag
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -fPIE -O3 -g

# Nomi eseguibili
NAME        = cub3D
NAME_BONUS  = cub3B
NAME_MEME   = cub3M

# ========================================================================== #
#                                 SOURCE FILES                              #
# ========================================================================== #

# Mandatory sources
SRC_MAIN   = mandatory/main.c
SRC_PARSE  = mandatory/parsing/extract_colors.c \
             mandatory/parsing/extract_elements.c \
             mandatory/parsing/handle_file.c \
             mandatory/parsing/parse_map.c \
             mandatory/parsing/parse_map_utils.c \
             mandatory/parsing/parsing_utils.c \
             mandatory/parsing/init_data.c

SRC_ENGINE = mandatory/engine/dda.c \
             mandatory/engine/handle_keys.c \
             mandatory/engine/draw.c \
             mandatory/engine/draw_utils.c \
             mandatory/engine/handle_keys_utils.c \
             mandatory/engine/free_mem.c

# Bonus sources
SRC_MAIN_BONUS   = bonus/main_bonus.c
SRC_PARSE_BONUS  = bonus/parsing/extract_colors_bonus.c \
                   bonus/parsing/extract_elements_bonus.c \
                   bonus/parsing/handle_file_bonus.c \
                   bonus/parsing/parse_map_bonus.c \
                   bonus/parsing/parse_map_utils_bonus.c \
                   bonus/parsing/parsing_utils_bonus.c \
                   bonus/parsing/init_data_bonus.c \
                   bonus/parsing/get_elements_2_bonus.c \
				   bonus/parsing/init_data_animation_bonus.c \
				   bonus/parsing/parse_textures.c \
				   bonus/parsing/parse_map_utils_2_bonus.c 

SRC_ENGINE_BONUS = bonus/engine/dda_bonus.c \
                   bonus/engine/handle_keys_bonus.c \
                   bonus/engine/draw_bonus.c \
                   bonus/engine/draw_utils_bonus.c \
                   bonus/engine/handle_keys_utils_bonus.c \
                   bonus/engine/free_mem_bonus.c \
                   bonus/engine/print_info_bonus.c \
                   bonus/engine/animation_bonus.c \
                   bonus/engine/doors.c \
                   bonus/engine/convert_color.c \
                   bonus/engine/free_mem_2_bonus.c \
                   bonus/engine/handle_keys_utils_2_bonus.c \
				   bonus/engine/render_map.c

# Headers
HEADERS = mandatory/cub3D.h
HEADERS_BONUS = bonus/cub3D_bonus.h

# Combined sources
SRC       = $(SRC_MAIN) $(SRC_PARSE) $(SRC_ENGINE)
SRC_BONUS = $(SRC_MAIN_BONUS) $(SRC_PARSE_BONUS) $(SRC_ENGINE_BONUS)

# ========================================================================== #
#                                 DIRECTORIES                               #
# ========================================================================== #

OBJ_DIR       = obj
OBJ_DIR_BONUS = obj/bonus
OBJ_DIR_MEME  = obj/meme

LIB_DIR = my_libft
MLX_DIR = minilibx-linux

# ========================================================================== #
#                                 OBJECT FILES                              #
# ========================================================================== #

OBJ      = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
OBJ_BONUS = $(addprefix $(OBJ_DIR_BONUS)/, $(SRC_BONUS:.c=.o))
OBJ_MEME  = $(addprefix $(OBJ_DIR_MEME)/, $(SRC_BONUS:.c=.o))

# ========================================================================== #
#                                 LIBRARIES                                 #
# ========================================================================== #

MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
THA_LIB = $(LIB_DIR)/mylibft.a

# ========================================================================== #
#                                 COLORS                                    #
# ========================================================================== #

RED     = \033[31m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m
RESET   = \033[0m
ERROR   = $(RED)✗

# ========================================================================== #
#                                 VARIABLES                                 #
# ========================================================================== #

BUILD = 0

# ========================================================================== #
#                                 MAIN TARGETS                              #
# ========================================================================== #

all: $(NAME)
	@if [ $(BUILD) -eq 1 ]; then \
		echo "$(GREEN)✔ Build completato$(RESET)"; \
	else \
		if [ $(BUILD) -eq 0 ]; then \
			echo "$(GREEN)✔ Già tutto compilato$(RESET)"; \
		fi \
	fi

bonus: CFLAGS += -D ISMA=0
bonus: $(NAME_BONUS)
	@if [ $(BUILD) -eq 1 ]; then \
		echo "$(GREEN)✔ Build bonus completato$(RESET)"; \
	else \
		if [ $(BUILD) -eq 0 ]; then \
			echo "$(GREEN)✔ Bonus già tutto compilato$(RESET)"; \
		fi \
	fi

meme: CFLAGS += -D ISMA=1
meme: $(NAME_MEME)
	@if [ $(BUILD) -eq 1 ]; then \
		echo "$(GREEN)✔ Build meme completato$(RESET)"; \
	else \
		if [ $(BUILD) -eq 0 ]; then \
			echo "$(GREEN)✔ Meme già tutto compilato$(RESET)"; \
		fi \
	fi

# ========================================================================== #
#                                 LIBRARIES                                 #
# ========================================================================== #

$(MLX_LIB):
	@echo "$(BLUE)➜ Compilazione della libreria $(YELLOW)MinilibX$(RESET)$(BLUE)...$(RESET)"
	@if ! $(MAKE) -C $(MLX_DIR) > /dev/null 2>&1; then \
		echo "$(ERROR) Errore durante la compilazione di MinilibX$(RESET)"; \
		exit 1; \
	fi
	@echo "$(GREEN)✔ MinilibX compilata$(RESET)"

$(THA_LIB):
	@echo "$(BLUE)➜ Compilazione della libreria $(YELLOW)my_libft$(RESET)$(BLUE)...$(RESET)"
	@if ! $(MAKE) -C $(LIB_DIR) > /dev/null 2>&1; then \
		echo "$(ERROR) Errore durante la compilazione della libreria my_libft$(RESET)"; \
		exit 1; \
	fi
	@echo "$(GREEN)✔ my_libft compilata$(RESET)"

# ========================================================================== #
#                                 COMPILATION RULES                         #
# ========================================================================== #

$(OBJ_DIR)/mandatory/%.o: mandatory/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ || { \
		echo "$(ERROR) Errore nella compilazione di $<$(RESET)"; \
		exit 1; \
	}

$(OBJ_DIR_BONUS)/bonus/%.o: bonus/%.c $(HEADERS_BONUS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ || { \
		echo "$(ERROR) Errore nella compilazione di $<$(RESET)"; \
		exit 1; \
	}

$(OBJ_DIR_MEME)/bonus/%.o: bonus/%.c $(HEADERS_BONUS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ || { \
		echo "$(ERROR) Errore nella compilazione di $<$(RESET)"; \
		exit 1; \
	}

# ========================================================================== #
#                                 EXECUTABLES                               #
# ========================================================================== #

$(NAME): $(OBJ) $(MLX_LIB) $(THA_LIB)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(MLX_LIB) $(THA_LIB) -lm -lX11 -lXext || { \
		echo "$(ERROR) Errore durante il linking finale$(RESET)"; \
		exit 1; \
	}
	@$(eval BUILD = 1)
	@echo "$(BLUE)➜ Creazione eseguibile $(NAME)...$(RESET)"
	@echo "$(GREEN)✔ Eseguibile $(NAME) generato$(RESET)"

$(NAME_BONUS): $(OBJ_BONUS) $(MLX_LIB) $(THA_LIB)
	@$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(NAME_BONUS) $(MLX_LIB) $(THA_LIB) -lm -lX11 -lXext || { \
		echo "$(ERROR) Errore durante il linking finale bonus$(RESET)"; \
		exit 1; \
	}
	@$(eval BUILD = 1)
	@echo "$(BLUE)➜ Creazione eseguibile $(NAME_BONUS)...$(RESET)"
	@echo "$(GREEN)✔ Eseguibile $(NAME_BONUS) generato$(RESET)"

$(NAME_MEME): $(OBJ_MEME) $(MLX_LIB) $(THA_LIB)
	@$(CC) $(CFLAGS) $(OBJ_MEME) -o $(NAME_MEME) $(MLX_LIB) $(THA_LIB) -lm -lX11 -lXext || { \
		echo "$(ERROR) Errore durante il linking finale meme$(RESET)"; \
		exit 1; \
	}
	@$(eval BUILD = 1)
	@echo "$(BLUE)➜ Creazione eseguibile $(NAME_MEME)...$(RESET)"
	@echo "$(GREEN)✔ Eseguibile $(NAME_MEME) generato$(RESET)"

# ========================================================================== #
#                                 CLEANUP                                   #
# ========================================================================== #

clean:
	@$(MAKE) -s -C $(LIB_DIR) clean > /dev/null 2>&1
	@echo "$(BLUE)➜ File oggetto da $(YELLOW)$(LIB_DIR)$(RESET) $(BLUE)rimossi$(RESET)"
	@$(MAKE) -s -C $(MLX_DIR) clean > /dev/null 2>&1
	@echo "$(BLUE)➜ File oggetto da $(YELLOW)$(MLX_DIR)$(RESET) $(BLUE)rimossi$(RESET)"
	@rm -rf $(OBJ_DIR) $(OBJ_DIR_BONUS) $(OBJ_DIR_MEME)
	@echo "$(BLUE)➜ File oggetto $(YELLOW)$(NAME)$(RESET) $(BLUE)rimossi$(RESET)"

fclean: clean
	@$(MAKE) -s -C $(LIB_DIR) fclean > /dev/null 2>&1
	@$(MAKE) -s -C $(MLX_DIR) clean > /dev/null 2>&1
	@rm -f $(NAME) $(NAME_BONUS) $(NAME_MEME)
	@echo "$(BLUE)➜ Eseguibili $(YELLOW)$(NAME)$(RESET), $(YELLOW)$(NAME_BONUS)$(RESET) e $(YELLOW)$(NAME_MEME)$(RESET) $(BLUE)rimossi$(RESET)"

re: fclean all

silent:
	@$(MAKE) all 2>&1 | grep -v '^make\[.*\]:'

.PHONY: all bonus meme clean fclean re silent
