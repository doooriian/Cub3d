#include "cub3d.h"

void	draw_minimap_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT)
	{
		dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_minimap_square(t_img *img, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			draw_minimap_pixel(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	render_minimap(t_game *data)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (j < data->map_width)
		{
			x = j * data->tile_size + data->map_offset_x;
			y = i * data->tile_size + data->map_offset_y;
			if (data->map_data.map[i][j] == '1')
				draw_minimap_square(&data->imgs.map, x, y, data->tile_size, 0x00888888);
			else if (data->map_data.map[i][j] == '0' || data->map_data.map[i][j] == 'N' || data->map_data.map[i][j] == 'S'
				|| data->map_data.map[i][j] == 'E' || data->map_data.map[i][j] == 'W')
				draw_minimap_square(&data->imgs.map, x, y, data->tile_size, 0xFFFFFF);
			else
				draw_minimap_square(&data->imgs.map, x, y, data->tile_size, 0x000000); // espaces vides
			j++;
		}
		i++;
	}
}

bool	is_ray_touching_wall(t_game *data, float ray_x, float ray_y)
{
	int	i;
	int	j;

	i = (int)ray_y / data->tile_size;
	j = (int)ray_x / data->tile_size;
	// Vérifiez indices hors map
	if (i < 0 || i >= data->map_height || j < 0 || j >= data->map_width)
		return (1);
	if (data->map_data.map[i][j] == '1')
		return (1);
	return (0);
}

void	draw_ray_line(t_game *data, t_player *player, float angle)
{
	float	ray_x;
	float	ray_y;
	float	cos_angle;
	float	sin_angle;

	ray_x = player->x;
	ray_y = player->y;
	cos_angle = cos(angle);
	sin_angle = sin(angle);
	while (!is_ray_touching_wall(data, ray_x, ray_y))
	{
		draw_minimap_pixel(&data->imgs.map, ray_x + data->map_offset_x, ray_y + data->map_offset_y, 0xFF0000);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
}

void	render_rays_on_minimap(t_game *data, t_player *player)
{
	int		i;
	int		ray_count;
	float	fraction;
	float	start_angle;

	i = 0;
	ray_count = RAYS;
	fraction = PI / 3 / ray_count; // Ajustez l'incrément en fonction du nombre de rayons
	start_angle = player->angle - PI / 6;
	while (i < ray_count)
	{
		draw_ray_line(data, player, start_angle);
		start_angle += fraction;
		i++;
	}
}

int update_minimap_loop(t_game *data)
{
	float		cos_angle;
	float		sin_angle;
	t_player	*player;

	player = &data->player;
	rotate_player(player);
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	move_player(data, cos_angle, sin_angle, data->tile_size);
	reset_player_var(player);

	render_minimap(data);
	render_rays_on_minimap(data, player);
	draw_minimap_square(&data->imgs.map, player->x - PLAYER_SIZE / 2 + data->map_offset_x,
		player->y - PLAYER_SIZE / 2 + data->map_offset_y, PLAYER_SIZE, 0xF7230C);
	mlx_put_image_to_window(data->mlx, data->win_map, data->imgs.map.img, 0, 0);
	return (0);
}
