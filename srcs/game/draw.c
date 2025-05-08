#include "cub3d.h"

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

void	draw_map(t_game *data)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			x = j * data->tile_size + data->map_offset_x;
			y = i * data->tile_size + data->map_offset_y;
			if (g_map[i][j] == 1)
				draw_square(&data->img, x, y, data->tile_size, 0x00888888);
			else
				draw_square(&data->img, x, y, data->tile_size, 0xFFFFFF);
			j++;
		}
		i++;
	}
}

bool	touch_wall(t_game *data, float ray_x, float ray_y)
{
	int	i;
	int	j;

	i = (int)ray_y / data->tile_size;
	j = (int)ray_x / data->tile_size;
	if (g_map[i][j] == 1)
		return (1);
	return (0);
}

void	draw_line(t_game *data, t_player *player, float start_x)
{
	float	ray_x;
	float	ray_y;
	float	cos_angle;
	float	sin_angle;

	ray_x = player->ray_x + player->ray_offset;
	ray_y = player->ray_y + player->ray_offset;
	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	while (!touch_wall(data, ray_x, ray_y))
	{
		put_pixel(&data->img, ray_x + data->map_offset_x, ray_y + data->map_offset_y, 0xFF0000);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
}

void	draw_rays(t_game *data, t_player *player)
{
	int		i;
	float	fraction;
	float	start_x;

	i = 0;
	fraction = PI / 3 / WIDTH;
	start_x = player->angle - PI / 6;
	while (i < WIDTH)
	{
		draw_line(data, player, start_x);
		start_x += fraction;
		i++;
	}
}

int	draw_loop(t_game *data)
{
	float		cos_angle;
	float		sin_angle;
	t_player	*player;

	player = &data->player;
	rotate_player(player);
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	move_player(player, cos_angle, sin_angle, data->tile_size);
	reset_player_var(player);
	draw_map(data);
	draw_rays(data, player);
	draw_square(&data->img, player->x + data->map_offset_x, player->y + data->map_offset_y, PLAYER_SIZE, 0xF7230C);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}
