# =============================================================================
# 🌟 GENERAL CONFIG & FLAGS 🌟
# =============================================================================

CC := cc
CFLAGS := -g -Wall -Wextra -Werror
LDFLAGS := -L/usr/local/lib -lreadline -Llibft -Lmlx
INCLUDES := -Iincludes -Ilibft/includes -Imlx
NAME := cub3D
LIBFT := $(LIBFT_A)

# =============================================================================
# 📂 SOURCES & OBJECTS 📂
# =============================================================================

# Main sources
SRCS_MAIN := srcs/main.c srcs/print_data.c

SRCS_UTILS := \
		srcs/utils/file_utils.c \
		srcs/utils/errors.c \
		srcs/utils/map_utils.c \
		srcs/utils/utils.c

SRCS_CONFIG := \
		srcs/parsing/config/init_config.c \
		srcs/parsing/config/config_utils.c \
		srcs/parsing/config/is_valid_config.c \
		srcs/parsing/config/load_config.c

SRCS_MAP := \
		srcs/parsing/map/init_map.c \
		srcs/parsing/map/validate_map.c \
		srcs/parsing/map/validate_horizontal.c \
		srcs/parsing/map/validate_space.c

SRCS_GAME := \
		srcs/game/draw.c \
		srcs/game/init.c \
		srcs/game/key_hook.c \
		srcs/game/player.c

SRCS_PARSING := srcs/parsing/get_map.c

# All sources combined
SRCS := $(SRCS_MAIN) $(SRCS_UTILS) $(SRCS_GAME) $(SRCS_PARSING) $(SRCS_CONFIG) $(SRCS_MAP)

OBJ_DIR := objs/
OBJ := $(SRCS:%.c=$(OBJ_DIR)/%.o)

MLX_DIR := mlx
MLX := $(MLX_DIR)/libmlx_Linux.a

LIBFT_DIR := libft
LIBFT_A := $(LIBFT_DIR)/libft.a

LIBS := $(LIBFT_A) $(MLX) -L/usr/lib/X11 -lXext -lX11 -lm


# =============================================================================
#	📊 PROGRESS BAR CONFIG 📊
# =============================================================================

BAR_LENGTH := 50
TOTAL_FILES := $(words $(SRCS))
COMPILED_FILES := 0

define progress_bar
	$(eval COMPILED_FILES=$(shell echo $$(($(COMPILED_FILES) + 1))))
	$(eval PROGRESS_PERCENT=$(shell echo $$(($(COMPILED_FILES) * 100 / $(TOTAL_FILES)))))
	$(eval FILLED_BAR_LENGTH=$(shell echo $$(($(PROGRESS_PERCENT) * $(BAR_LENGTH) / 100))))
	@printf "\rCompiling [\033[0;36m"
	@for i in $(shell seq 1 $(FILLED_BAR_LENGTH)); do printf "#"; done
	@for i in $(shell seq 1 $(shell echo $$(($(BAR_LENGTH) - $(FILLED_BAR_LENGTH))))); do printf " "; done
	@printf "\033[0m] $(PROGRESS_PERCENT)%%"
endef

# =============================================================================
# 🏗️ RULES 🏗️
# =============================================================================

all: libft $(NAME)
	@echo "\n🎉 Compilation of $(NAME)!\n"

$(NAME): $(MLX) $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBS) -o $(NAME)
	@echo "\n🎉 Compilation of $(NAME)!\n"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(call progress_bar)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


MAPS := $(wildcard maps/*.cub)

maps_win:
	@for file in $(MAPS); do \
		sed -i 's/\r$$//' $$file; \
	done
	@echo "Conversion des fichiers de maps en format Unix : \033[1;32mOK\033[0m"

.PHONY: maps_win

# =============================================================================
# LIBFT
# =============================================================================

libft:
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

clean_libft:
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory

fclean_libft:
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory

re_libft:
	@$(MAKE) -C $(LIBFT_DIR) re --no-print-directory

# =============================================================================
# MLX
# =============================================================================

# @if [ ! -d "mlx/mlx.a" ]; then \
# 		echo "Building Minilibx..."; \
# 		$(MAKE) -C mlx;
# 	else \
# 		echo "Minilibx already built."; \
# 	fi

$(MLX):
	@$(MAKE) -C $(MLX_DIR)

$(MLX_DIR):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "Cloning Minilibx..."; \
		git clone https://github.com/42paris/minilibx-linux.git $(MLX_DIR); \
	fi
	$(MAKE) -C mlx;

clean_mlx:
	@$(MAKE) -C $(MLX_DIR) clean
	@echo "Clean of Minilibx : \033[1;32mOK\033[0m"

fclean_mlx: clean_mlx

re_mlx: fclean_mlx $(MLX)

# =============================================================================
# CLEANING RULES
# =============================================================================

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Clean de $(NAME) : \033[1;32mOK\033[0m"

fclean: clean #fclean_libft
	@rm -f $(NAME)
	@echo "Fclean de $(NAME) : \033[1;32mOK\033[0m"

re: fclean all

# =============================================================================
# 💼 PHONY RULES 💼
# =============================================================================

.PHONY: all clean fclean re libft clean_libft fclean_libft re_libft clean_mlx fclean_mlx re_mlx
