/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_rendering_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doley <doley@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:18:22 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/18 14:53:52 by doley            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	calculate_wall_height(t_game *game, t_ray *ray)
{
	int	line_height;

	line_height = (int)(HEIGHT / (ray->perp_wall_dist
				* cos(game->player.angle - ray->ray_angle)));
	game->draw_start = -line_height / 2 + HEIGHT / 2;
	game->draw_end = line_height / 2 + HEIGHT / 2;
}

void	draw_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;
	int		width;

	width = img->line_length / (img->bits_per_pixel / 8);
	if (x < 0 || x >= width || y < 0 || y >= width)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_line(t_game *game, int x, t_point draw_s_e, int color)
{
	int	y;
	int	draw_start;
	int	draw_end;

	draw_start = draw_s_e.x;
	draw_end = draw_s_e.y;
	y = draw_start;
	while (y < draw_end)
	{
		draw_pixel(&game->imgs.base, x, y, color);
		y++;
	}
}

static t_img	*get_sprite_texture(t_game *game, t_ray *ray, int i)
{
	while (i < game->sprite_count)
	{
		if (game->sprites[i].active
			&& game->sprites[i].x == ray->map_x
			&& game->sprites[i].y == ray->map_y)
		{
			if (game->sprites[i].frame == 0)
				return (&game->imgs.sprite1);
			if (game->sprites[i].frame == 1)
				return (&game->imgs.sprite2);
			if (game->sprites[i].frame == 2)
				return (&game->imgs.sprite3);
		}
		i++;
	}
	return (NULL);
}

t_img	*get_texture(t_game *game, t_ray *ray)
{
	int		i;
	t_img	*sprite;

	i = 0;
	sprite = get_sprite_texture(game, ray, i);
	if (sprite)
		return (sprite);
	if (game->map_data.map[ray->map_y][ray->map_x] == 'D')
	{
		if (game->map_doors && game->map_doors[ray->map_y][ray->map_x] == '1')
			return (&game->imgs.door);
	}
	if (ray->side == 0 && ray->dir_x < 0)
		return (&game->imgs.we);
	if (ray->side == 0 && ray->dir_x >= 0)
		return (&game->imgs.ea);
	if (ray->side == 1 && ray->dir_y < 0)
		return (&game->imgs.no);
	return (&game->imgs.so);
}

// t_img	*get_texture(t_game *game, t_ray *ray)
// {
// 	int i;

// 	i = 0;	// PAS OTPIMISE !!!!!!!!!!!!!!!!!!!!!!!!!!! UTILISER MAP DOORS ET AJOUTER SPRITES DEDANS
// 	while (i < game->sprite_count)
// 	{
// 		if (game->sprites[i].active &&
// 			game->sprites[i].x == ray->map_x &&
// 			game->sprites[i].y == ray->map_y)
// 		{
// 			if (game->sprites[i].frame == 0)
// 				return (&game->imgs.sprite1);
// 			if (game->sprites[i].frame == 1)
// 				return (&game->imgs.sprite2);
// 			if (game->sprites[i].frame == 2)
// 				return (&game->imgs.sprite3);
// 		}
// 		i++;
// 	}
// 	if (game->map_data.map[ray->map_y][ray->map_x] == 'D')
// 	{
// 		if (game->map_doors && game->map_doors[ray->map_y][ray->map_x] == '1')
// 			return (&game->imgs.door);
// 	}
// 	if (ray->side == 0 && ray->dir_x < 0)
// 		return (&game->imgs.we);
// 	if (ray->side == 0 && ray->dir_x >= 0)
// 		return (&game->imgs.ea);
// 	if (ray->side == 1 && ray->dir_y < 0)
// 		return (&game->imgs.no);
// 	return (&game->imgs.so);
// }
