/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 22:52:48 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/13 22:52:48 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		draw_pixel(&game->imgs.map, ray_x + game->map_offset_x,
			ray_y + game->map_offset_y, 0xFF0000);
		ray_x += cos_angle;
		if (is_ray_touching_wall(game, ray_x, ray_y))
			break ;
		ray_y += sin_angle;
		if (is_ray_touching_wall(game, ray_x, ray_y))
			break ;
	}
}
