NAME = Cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c draw.c init.c key_hook.c player.c
OBJS = ${SRCS:.c=.o}

RM = rm -f

MLX_DIR = ./mlx
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib/X11 -lXext -lX11 -lm

all : mlx_build $(NAME)

mlx_build :
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

clean :
	$(RM) $(OBJS)
	$(MAKE) -C $(MLX_DIR) clean

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all mlx_build clean fclean re

