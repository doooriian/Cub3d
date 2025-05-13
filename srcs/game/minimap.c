#include "cub3d.h"

void	draw_square(t_img *img, t_point point, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			draw_pixel(img, point.x + j, point.y + i, color);
			j++;
		}
		i++;
	}
}

void	render_minimap(t_game *game)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			x = j * game->tile_size + game->map_offset_x;
			y = i * game->tile_size + game->map_offset_y;
			if (game->map_data.map[i][j] == '1')
				draw_square(&game->imgs.map, (t_point){x, y}, game->tile_size, 0x00888888);
			else if (game->map_data.map[i][j] == '0' || is_char_player(game->map_data.map[i][j]))
				draw_square(&game->imgs.map, (t_point){x, y}, game->tile_size, 0xFFFFFF);
			else
				draw_square(&game->imgs.map, (t_point){x, y}, game->tile_size, 0x000000);
			j++;
		}
		i++;
	}
}

bool	is_ray_touching_wall(t_game *game, float ray_x, float ray_y)
{
	int	i;
	int	j;

	i = (int)ray_y / game->tile_size;
	j = (int)ray_x / game->tile_size;
	if (i < 0 || i >= game->map_height || j < 0 || j >= game->map_width)
		return (1);
	if (game->map_data.map[i][j] == '1')
		return (1);
	return (0);
}

void	draw_ray_line(t_game *game, t_player *player, float angle)
{
	float	ray_x;
	float	ray_y;
	float	cos_angle;
	float	sin_angle;

	ray_x = player->x;
	ray_y = player->y;
	cos_angle = cos(angle);
	sin_angle = sin(angle);
	while (!is_ray_touching_wall(game, ray_x, ray_y))
	{
		draw_pixel(&game->imgs.map, ray_x + game->map_offset_x, ray_y + game->map_offset_y, 0xFF0000);
		ray_x += cos_angle;
		if (is_ray_touching_wall(game, ray_x, ray_y))
			break ;
		ray_y += sin_angle;
		if (is_ray_touching_wall(game, ray_x, ray_y))
			break ;
	}
}

void	render_rays_on_minimap(t_game *game, t_player *player)
{
	int		i;
	int		ray_count;
	float	fraction;
	float	start_angle;

	i = 0;
	ray_count = RAYS;
	fraction = PI / 3 / ray_count;
	start_angle = player->angle; //  - PI / 6
	while (i < ray_count)
	{
		draw_ray_line(game, player, start_angle);
		start_angle += fraction;
		i++;
	}
}

int	update_minimap_loop(t_game *game)
{
	t_point	pos;

	render_minimap(game);
	if (game->debug)
		render_rays_on_minimap(game, &game->player);
	pos.x = game->player.x - PLAYER_SIZE / 2 + game->map_offset_x;
	pos.y = game->player.y - PLAYER_SIZE / 2 + game->map_offset_y;
	draw_square(&game->imgs.map, pos, PLAYER_SIZE, 0xF7230C);
	mlx_put_image_to_window(game->mlx, game->win_map, game->imgs.map.img, 0, 0);
	return (0);
}
