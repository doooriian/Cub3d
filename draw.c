#include "cub.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_square(t_img *img, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			if (g_map[i][j] == 1)
				draw_square(&data->img, j * data->tile_size, i * data->tile_size, data->tile_size, 0x00888888);
			else
				draw_square(&data->img, j * data->tile_size, i * data->tile_size, data->tile_size, 0xFFFFFF);
			j++;
		}
		i++;
	}
}

int	draw_loop(t_data *data)
{
	float		cos_angle;
	float		sin_angle;
	t_player	*player;

	player = &data->player;
	rotate_player(player);
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	move_player(player, cos_angle, sin_angle, data->tile_size);
	player->tmp_x = player->x;
	player->tmp_y = player->y;
	draw_map(data);
	draw_square(&data->img, player->x, player->y, PLAYER_SIZE, 0xF7230C);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}