/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_rendering_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doley <doley@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:18:22 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/14 14:49:12 by doley            ###   ########.fr       */
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

	if (x < 0 || x >= img->line_length / (img->bits_per_pixel / 8)
		|| y < 0 || y >= img->line_length / (img->bits_per_pixel / 8))
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

t_img	*get_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0 && ray->dir_x < 0)
		return (&game->imgs.we);
	if (ray->side == 0 && ray->dir_x >= 0)
		return (&game->imgs.ea);
	if (ray->side == 1 && ray->dir_y < 0)
		return (&game->imgs.no);
	return (&game->imgs.so);
}
