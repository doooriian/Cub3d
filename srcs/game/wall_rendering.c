/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_rendering.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:18:52 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/13 23:18:52 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	calculate_tex_x(t_game *game, t_ray *ray)
{
	int		tex_x;
	double	wall_x;

	if (ray->side == 0)
		wall_x = (game->player.y / (float)game->tile_size)
			+ ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = (game->player.x / (float)game->tile_size)
			+ ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)get_texture(game, ray)->width);
	if (ray->side == 0 && ray->dir_x > 0)
		tex_x = get_texture(game, ray)->width - tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		tex_x = get_texture(game, ray)->width - tex_x - 1;
	tex_x = get_texture(game, ray)->width - tex_x - 1;
	return (tex_x);
}

static int	calculate_tex_y(t_game *game, t_ray *ray, int tex_pos)
{
	int		tex_y;

	tex_y = (int)tex_pos & (get_texture(game, ray)->height - 1);
	return (tex_y);
}

void	draw_wall_tx(t_game *game, t_ray *ray, int x)
{
	double	step;
	double	tex_pos;
	int		line_height;
	int		color;
	int		y;

	line_height = game->draw_end - game->draw_start;
	step = 1.0 * get_texture(game, ray)->height / line_height;
	tex_pos = (game->draw_start - HEIGHT / 2 + line_height / 2) * step;
	if (game->draw_start < 0)
		tex_pos += step * (0 - game->draw_start);
	y = game->draw_start;
	if (y < 0)
		y = 0;
	while (y < game->draw_end && y < HEIGHT - 1)
	{
		tex_pos += step;
		color = get_pixel_color(get_texture(game, ray),
				calculate_tex_x(game, ray),
				calculate_tex_y(game, ray, tex_pos));
		if (ray->side == 1)
			color = (color >> 1) & 0x7F7F7F;
		draw_pixel(&game->imgs.base, x, y, color);
		y++;
	}
}

void	draw_ceiling_and_floor(t_game *game, int x)
{
	int	ceiling_color;
	int	floor_color;

	ceiling_color = get_rgb_color(game->map_data.top_color[0],
			game->map_data.top_color[1], game->map_data.top_color[2]);
	floor_color = get_rgb_color(game->map_data.floor_color[0],
			game->map_data.floor_color[1], game->map_data.floor_color[2]);
	draw_line(game, x, (t_point){0, game->draw_start}, ceiling_color);
	draw_line(game, x, (t_point){game->draw_end, HEIGHT}, floor_color);
}

void	render_walls(t_game *game)
{
	int		x;
	t_ray	ray;
	float	ray_angle;

	x = 0;
	while (x < WIDTH)
	{
		ray_angle = game->player.angle - (PI / 6)
			+ ((float)x / (float)WIDTH) * (PI / 3);
		init_ray(game, &ray, ray_angle);
		if (perform_dda(game, &ray))
		{
			calculate_wall_height(game, &ray);
			draw_ceiling_and_floor(game, x);
			draw_wall_tx(game, ray, x);
		}
		x++;
	}
}
