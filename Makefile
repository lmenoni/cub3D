# Comportamento predefinito
.DEFAULT_GOAL := silent

# Configurazioni principali
CC	  = cc
CFLAGS  = -Wall -Wextra -Werror -fPIE -o3
NAME	= cub3D

# Struttura sorgenti in diverse cartelle
SRC_MAIN   = mandatory/main.c
SRC_PARSE  = mandatory/parsing/extract_colors.c mandatory/parsing/extract_elements.c mandatory/parsing/handle_file.c mandatory/parsing/parse_map.c mandatory/parsing/parse_map_utils.c mandatory/parsing/parsing_utils.c mandatory/parsing/init_data.c
SRC_ENGINE = mandatory/engine/dda.c mandatory/engine/handle_keys.c mandatory/engine/draw.c mandatory/engine/draw_utils.c mandatory/engine/handle_keys_utils.c mandatory/engine/free_mem.c

SRC_MAIN_BONUS   = bonus/main_bonus.c
SRC_PARSE_BONUS  = bonus/parsing/extract_colors_bonus.c bonus/parsing/extract_elements_bonus.c bonus/parsing/handle_file_bonus.c bonus/parsing/parse_map_bonus.c bonus/parsing/parse_map_utils_bonus.c bonus/parsing/parsing_utils_bonus.c bonus/parsing/init_data_bonus.c
SRC_ENGINE_BONUS = bonus/engine/dda_bonus.c bonus/engine/handle_keys_bonus.c bonus/engine/draw_bonus.c bonus/engine/draw_utils_bonus.c bonus/engine/handle_keys_utils_bonus.c bonus/engine/free_mem_bonus.c
# Per aggiungere altre cartelle:
# SRC_RENDER = rendering/file1.c rendering/file2.c
# SRC_LOGIC  = logic/file1.c logic/file2.c

# Combinazione di tutti i sorgenti
SRC	 = $(SRC_MAIN) $(SRC_PARSE) $(SRC_ENGINE)
SRC_BONUS = $(SRC_MAIN_BONUS) $(SRC_PARSE_BONUS) $(SRC_ENGINE_BONUS)
# Aggiungi qui altre cartelle quando necessario:
# SRC += $(SRC_RENDER) $(SRC_LOGIC)

HEADERS = cub3D.h
OBJ_DIR = obj
OBJ_BONUS_DIR = obj_bonus  # Aggiungi questa linea

# Trasforma tutti i percorsi in nomi oggetto nella directory obj
OBJ = $(SRC:.c=.o)
OBJ := $(addprefix $(OBJ_DIR)/, $(OBJ))

OBJ_BONUS = $(SRC_BONUS:.c=.o)
OBJ_BONUS := $(addprefix $(OBJ_BONUS_DIR)/, $(OBJ_BONUS))  # Usa directory separata
LIB_DIR = my_libft
MLX_DIR = minilibx-linux
BUILD = 0

# Librerie
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
THA_LIB = $(LIB_DIR)/mylibft.a

# Colori ANSI
RED	 = \033[31m
ERROR = $(RED)✗
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE	= \033[34m
RESET   = \033[0m

all: $(NAME)
	@if [ $(BUILD) -eq 1 ]; then \
		echo "$(GREEN)✔ Build completato$(RESET)"; \
	else \
		if [ $(BUILD) -eq 0 ]; then \
			echo "$(GREEN)✔ Già tutto compilato$(RESET)"; \
		fi \
	fi

$(MLX_LIB):
	@echo "$(BLUE)➜ Compilazione della libreria $(YELLOW)MinilibX$(RESET)$(BLUE)...$(RESET)"
	@if ! $(MAKE) -C $(MLX_DIR) > /dev/null 2>&1; then \
		echo "$(ERROR) Errore durante la compilazione di MinilibX$(RESET)"; \
		exit 1; \
	fi
	@echo "$(GREEN)✔ MinilibX compilata$(RESET)"

$(THA_LIB):
	@echo "$(BLUE)➜ Compilazione della libreria $(YELLOW)tha_supreme$(RESET)$(BLUE)...$(RESET)"
	@if ! $(MAKE) -C $(LIB_DIR) > /dev/null 2>&1; then \
		echo "$(ERROR) Errore durante la compilazione della libreria tha_supreme_lib$(RESET)"; \
		exit 1; \
	fi
	@echo "$(GREEN)✔ tha_supreme compilata$(RESET)"

# Crea VPATH per indicare a Make dove cercare i file sorgente
VPATH = mandatory:mandatory/parsing:mandatory/engine:bonus:bonus/parsing:bonus/engine
# Per aggiungere altre cartelle al percorso di ricerca:
# VPATH += :rendering:logic

# Una singola regola di compilazione per tutti i file
$(OBJ_DIR)/%.o: %.c $(HEADERS) | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ || { \
		echo "$(ERROR) Errore nella compilazione di $<$(RESET)"; \
		exit 1; \
	}

$(OBJ_BONUS_DIR)/%.o: %.c $(HEADERS) | $(OBJ_BONUS_DIR)  # Correggi qui
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ || { \
		echo "$(ERROR) Errore nella compilazione di $<$(RESET)"; \
		exit 1; \
	}

bonus: $(MLX_LIB) $(THA_LIB) $(OBJ_BONUS)
	@$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(NAME) $(MLX_LIB) -L$(LIB_DIR) -l:$(notdir $(THA_LIB)) -lm -lX11 -lXext || { \
		echo "$(ERROR) Errore durante il linking finale per la versione bonus$(RESET)"; \
		exit 1; \
	}
	@echo "$(BLUE)➜ Creazione eseguibile $(NAME) (versione bonus)...$(RESET)"
	@echo "$(GREEN)✔ Eseguibile $(NAME) (bonus) generato$(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_BONUS_DIR):  # Aggiungi questo target
	@mkdir -p $(OBJ_BONUS_DIR)

$(NAME): $(OBJ) $(MLX_LIB) $(THA_LIB)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(MLX_LIB) -L$(LIB_DIR) -l:$(notdir $(THA_LIB)) -lm -lX11 -lXext || { \
		echo "$(ERROR) Errore durante il linking finale$(RESET)"; \
		exit 1; \
	}
	@$(eval BUILD = 1)
	@echo "$(BLUE)➜ Creazione eseguibile $(NAME)...$(RESET)"
	@echo "$(GREEN)✔ Eseguibile $(NAME) generato$(RESET)"

clean:
	@$(MAKE) -s -C $(LIB_DIR) clean > /dev/null 2>&1
	@echo "$(BLUE)➜ File oggetto da $(YELLOW)$(LIB_DIR)$(RESET) $(BLUE)rimossi$(RESET)"
	@$(MAKE) -s -C $(MLX_DIR) clean > /dev/null 2>&1
	@echo "$(BLUE)➜ File oggetto da $(YELLOW)$(MLX_DIR)$(RESET) $(BLUE)rimossi$(RESET)"
	@rm -rf $(OBJ_DIR) $(OBJ_BONUS_DIR)  # Rimuovi entrambe le directory
	@echo "$(BLUE)➜ File oggetto $(YELLOW)$(NAME)$(RESET) $(BLUE)rimossi$(RESET)"

fclean: clean
	@$(MAKE) -s -C $(LIB_DIR) fclean > /dev/null 2>&1
	@$(MAKE) -s -C $(MLX_DIR) clean > /dev/null 2>&1
	@rm -f $(NAME)
	@echo "$(BLUE)➜ Eseguibile $(YELLOW)$(NAME)$(RESET) $(BLUE)rimosso$(RESET)"

re: fclean all

silent:
	@$(MAKE) all 2>&1 | grep -v '^make\[.*\]:'

.PHONY: all clean fclean re lib_check silent bonus