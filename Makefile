# =============================================================================
# 🌟 GENERAL CONFIG & FLAGS 🌟
# =============================================================================

CC := cc
CFLAGS := -g -Wall -Wextra -Werror
LDFLAGS := -L/usr/local/lib -lreadline -Llibft
INCLUDES := -Iincludes -Ilibft/includes -Imlx/include -Imlx/include/MLX42
NAME := cub3D
LIBFT := $(LIBFT_A)

# =============================================================================
# 📂 SOURCES & OBJECTS 📂
# =============================================================================

# Main sources
SRCS_MAIN := srcs/main.c srcs/errors.c

SRCS_PARSING := srcs/parsing/file_utils.c\
	srcs/parsing/map_utils.c \
	srcs/parsing/get_map.c \
	srcs/parsing/init_config.c \
	srcs/parsing/validate_map.c

# All sources combined
SRCS := $(SRCS_MAIN) $(SRCS_PARSING)

OBJ_DIR := objs/
OBJ := $(SRCS:%.c=$(OBJ_DIR)/%.o)

MLX_DIR := mlx
MLX := $(MLX_DIR)/build/libmlx42.a

LIBFT_DIR := libft
LIBFT_A := $(LIBFT_DIR)/libft.a

LIBS := $(LIBFT_A) $(MLX) -pthread -ldl -lm -lglfw


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

$(MLX): $(MLX_DIR)
	@if [ ! -d "$(MLX_DIR)/build" ]; then \
		echo "Building MLX42..."; \
		cd $(MLX_DIR) && cmake -B build && cmake --build build -j4; \
	else \
		echo "MLX42 already built."; \
	fi

$(MLX_DIR):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "Cloning MLX42..."; \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR); \
	fi

clean_mlx:
	@rm -rf $(MLX_DIR)/build
	@echo "Clean of MLX42 : \033[1;32mOK\033[0m"

fclean_mlx: clean_mlx

re_mlx: fclean_mlx $(MLX)

# =============================================================================
# CLEANING RULES
# =============================================================================

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Clean de $(NAME) : \033[1;32mOK\033[0m"

fclean: clean fclean_libft
	@rm -f $(NAME)
	@echo "Fclean de $(NAME) : \033[1;32mOK\033[0m"

re: fclean all

# =============================================================================
# 💼 PHONY RULES 💼
# =============================================================================

.PHONY: all clean fclean re libft clean_libft fclean_libft re_libft clean_mlx fclean_mlx re_mlx
