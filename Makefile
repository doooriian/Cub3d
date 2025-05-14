# =============================================================================
# 🌟 GENERAL CONFIG & FLAGS 🌟
# =============================================================================

CC := cc
CFLAGS := -g -Wall -Wextra -Werror
LDFLAGS := -L/usr/local/lib -lreadline -Llibft -Lmlx
INCLUDES := -Iincludes -Ilibft/includes -Imlx
INCLUDES_BONUS := -Iincludes_bonus -Ilibft/includes -Imlx
NAME := cub3D
NAME_BONUS := cub3D_bonus
LIBFT := $(LIBFT_A)

# =============================================================================
# 📂 SOURCES 📂
# =============================================================================

# Main sources
SRCS_MAIN := srcs/main.c srcs/print_data.c srcs/main_utils.c

SRCS_UTILS := \
		srcs/utils/file_utils.c \
		srcs/utils/errors.c \
		srcs/utils/map_utils.c \
		srcs/utils/utils.c \
		srcs/utils/frees.c \
		srcs/utils/ft_split_with_sep.c \
		srcs/utils/ft_atoi_safe.c

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
		srcs/game/init_game.c \
		srcs/game/key_hook.c \
		srcs/game/player.c \
		srcs/game/player_utils.c \
		srcs/game/raycasting.c \
		srcs/game/wall_rendering.c \
		srcs/game/wall_rendering_utils.c

SRCS_PARSING := srcs/parsing/get_map.c

SRCS_COMPASS := \
		srcs/game/compass/compass_utils.c \
		srcs/game/compass/compass.c \
		srcs/game/compass/draw_filled_triangle.c

# =============================================================================
# 📂 SOURCES BONUS 📂
# =============================================================================

SRCS_BONUS_MAIN := srcs_bonus/main.c srcs_bonus/print_data.c srcs_bonus/main_utils.c

SRCS_BONUS_UTILS := \
		srcs_bonus/utils/file_utils.c \
		srcs_bonus/utils/errors.c \
		srcs_bonus/utils/map_utils.c \
		srcs_bonus/utils/utils.c \
		srcs_bonus/utils/frees.c \
		srcs_bonus/utils/ft_split_with_sep.c \
		srcs_bonus/utils/ft_atoi_safe.c

SRCS_BONUS_CONFIG := \
		srcs_bonus/parsing/config/init_config.c \
		srcs_bonus/parsing/config/config_utils.c \
		srcs_bonus/parsing/config/is_valid_config.c \
		srcs_bonus/parsing/config/load_config.c

SRCS_BONUS_MAP := \
		srcs_bonus/parsing/map/init_map.c \
		srcs_bonus/parsing/map/validate_map.c \
		srcs_bonus/parsing/map/validate_horizontal.c \
		srcs_bonus/parsing/map/validate_space.c

SRCS_BONUS_GAME := \
		srcs_bonus/game/init_game.c \
		srcs_bonus/game/key_hook.c \
		srcs_bonus/game/mouse.c \
		srcs_bonus/game/player.c \
		srcs_bonus/game/player_utils.c \
		srcs_bonus/game/raycasting.c \
		srcs_bonus/game/wall_rendering.c \
		srcs_bonus/game/wall_rendering_utils.c \
		srcs_bonus/game/door.c

SRCS_BONUS_MINIMAP := \
		srcs_bonus/game/minimap/minimap.c \
		srcs_bonus/game/minimap/minimap_utils.c \
		srcs_bonus/game/minimap/draw_minimap.c

SRCS_BONUS_PARSING := srcs_bonus/parsing/get_map.c

SRCS_BONUS_COMPASS := \
		srcs_bonus/game/compass/compass_utils.c \
		srcs_bonus/game/compass/compass.c \
		srcs_bonus/game/compass/draw_filled_triangle.c

# All sources combined
SRCS := $(SRCS_MAIN) $(SRCS_UTILS) $(SRCS_GAME) $(SRCS_PARSING) $(SRCS_CONFIG) $(SRCS_MAP) $(SRCS_COMPASS)
SRCS_BONUS := $(SRCS_BONUS_MAIN) $(SRCS_BONUS_UTILS) $(SRCS_BONUS_GAME) $(SRCS_BONUS_PARSING) $(SRCS_BONUS_CONFIG) $(SRCS_BONUS_MAP) $(SRCS_BONUS_MINIMAP) $(SRCS_BONUS_COMPASS)

# =============================================================================
# 📂 OBJECTS 📂
# =============================================================================

OBJ_DIR := objs/
OBJ_DIR_BONUS := objs_bonus/
OBJ := $(SRCS:%.c=$(OBJ_DIR)/%.o)
OBJ_BONUS := $(SRCS_BONUS:%.c=$(OBJ_DIR_BONUS)/%.o)

LIBFT_DIR := libft
LIBFT_A := $(LIBFT_DIR)/libft.a

MLX_DIR := mlx
MLX := $(MLX_DIR)/libmlx_Linux.a

LIBS := $(LIBFT_A) $(MLX) -L/usr/lib/X11 -lXext -lX11 -lm -lreadline

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

# BONUS PROGRESS BAR
TOTAL_FILES_BONUS := $(words $(SRCS_BONUS))
COMPILED_FILES_BONUS := 0

define progress_bar_bonus
	$(eval COMPILED_FILES_BONUS=$(shell echo $$(($(COMPILED_FILES_BONUS) + 1))))
	$(eval PROGRESS_PERCENT=$(shell echo $$(($(COMPILED_FILES_BONUS) * 100 / $(TOTAL_FILES_BONUS)))))
	$(eval FILLED_BAR_LENGTH=$(shell echo $$(($(PROGRESS_PERCENT) * $(BAR_LENGTH) / 100))))
	@printf "\rCompiling [\033[0;36m"
	@for i in $(shell seq 1 $(FILLED_BAR_LENGTH)); do printf "#"; done
	@for i in $(shell seq 1 $(shell echo $$(($(BAR_LENGTH) - $(FILLED_BAR_LENGTH))))); do printf " "; done
	@printf "\033[0m] $(PROGRESS_PERCENT)%%"
endef

# =============================================================================
# 🏗️ RULES 🏗️
# =============================================================================

all: $(MLX_DIR) $(MLX) libft $(NAME)
	@echo "\n🎉 Compilation of $(NAME)!\n"

bonus: $(MLX_DIR) $(MLX) libft $(NAME_BONUS)
	@echo "\n🎉 Compilation of $(NAME_BONUS)!\n"

$(NAME_BONUS): $(MLX) $(LIBFT) $(OBJ_BONUS)
	@$(CC) $(CFLAGS) $(INCLUDES_BONUS) $(OBJ_BONUS) $(LIBS) -o $(NAME_BONUS)
	@echo "\n🎉 Compilation of $(NAME_BONUS)!\n"

$(NAME): $(MLX) $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBS) -o $(NAME)
	@echo "\n🎉 Compilation of $(NAME)!\n"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(call progress_bar)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR_BONUS)/%.o: %.c
	@mkdir -p $(@D)
	$(call progress_bar_bonus)
	@$(CC) $(CFLAGS) $(INCLUDES_BONUS) -c $< -o $@


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
# 📥 MLX RULES 📥
# =============================================================================

$(MLX_DIR):
	@git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR)

$(MLX):
	@$(MAKE) -C $(MLX_DIR)

clean_mlx:
	@$(MAKE) -C $(MLX_DIR) clean

fclean_mlx:
	@$(MAKE) -C $(MLX_DIR) clean

re_mlx: fclean_mlx $(MLX)

# =============================================================================
# CLEANING RULES
# =============================================================================

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Clean de $(NAME) : \033[1;32mOK\033[0m"

fclean: clean # fclean_libft
	@rm -f $(NAME)
	@echo "Fclean de $(NAME) : \033[1;32mOK\033[0m"

re: fclean all

clean_bonus:
	@rm -rf $(OBJ_DIR_BONUS)
	@echo "Clean de $(NAME_BONUS) : \033[1;32mOK\033[0m"

fclean_bonus: clean_bonus # fclean_libft
	@rm -f $(NAME_BONUS)
	@echo "Fclean de $(NAME_BONUS) : \033[1;32mOK\033[0m"

re_bonus: fclean_bonus bonus

# =============================================================================
# 💼 PHONY RULES 💼
# =============================================================================

.PHONY: all clean fclean re libft clean_libft fclean_libft re_libft clean_mlx fclean_mlx re_mlx
