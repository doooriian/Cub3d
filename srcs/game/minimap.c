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

void	draw_ray_with_dda(t_game *game, t_player *player, float ray_angle)
{
	t_ray	ray;
	int		tile_size = game->tile_size;

	// Position de départ
	ray.map_x = (int)(player->x / tile_size);
	ray.map_y = (int)(player->y / tile_size);

	// Direction du rayon
	ray.dir_x = cos(ray_angle);
	ray.dir_y = sin(ray_angle);

	// Longueur de chaque pas dans x et y
	ray.delta_dist_x = fabs(1 / ray.dir_x);
	ray.delta_dist_y = fabs(1 / ray.dir_y);

	// Initialisation des étapes et distances initiales
	if (ray.dir_x < 0)
	{
		ray.step_x = -1;
		ray.side_dist_x = (player->x / tile_size - ray.map_x) * ray.delta_dist_x;
	}
	else
	{
		ray.step_x = 1;
		ray.side_dist_x = (ray.map_x + 1.0 - player->x / tile_size) * ray.delta_dist_x;
	}

	if (ray.dir_y < 0)
	{
		ray.step_y = -1;
		ray.side_dist_y = (player->y / tile_size - ray.map_y) * ray.delta_dist_y;
	}
	else
	{
		ray.step_y = 1;
		ray.side_dist_y = (ray.map_y + 1.0 - player->y / tile_size) * ray.delta_dist_y;
	}

	// Avancer jusqu'à collision
	while (ray.map_x >= 0 && ray.map_x < game->map_width
		&& ray.map_y >= 0 && ray.map_y < game->map_height
		&& game->map_data.map[ray.map_y][ray.map_x] != '1')
	{
		if (game->debug)
		{
			int pixel_x = ray.map_x * tile_size + tile_size / 2 + game->map_offset_x;
			int pixel_y = ray.map_y * tile_size + tile_size / 2 + game->map_offset_y;
			draw_minimap_pixel(&game->imgs.map, pixel_x, pixel_y, 0xFF0000); // Rouge
		}
		if (ray.side_dist_x < ray.side_dist_y)
		{
			ray.side_dist_x += ray.delta_dist_x;
			ray.map_x += ray.step_x;
			ray.side = 0;
		}
		else
		{
			ray.side_dist_y += ray.delta_dist_y;
			ray.map_y += ray.step_y;
			ray.side = 1;
		}
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
		draw_ray_with_dda(data, player, start_angle);
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
