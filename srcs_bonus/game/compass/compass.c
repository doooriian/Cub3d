/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compass.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doley <doley@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:27:54 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/14 14:48:23 by doley            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_compass_arrows(t_game *game, int cx, int cy, float base_angle)
{
	int		i;
	float	angle;
	int		color;
	t_point	center;

	center.x = cx;
	center.y = cy;
	i = 0;
	while (i < 4)
	{
		angle = base_angle + i * (PI / 2);
		if (i == 0)
			color = COLOR_NORTH;
		else
			color = COLOR_OTHER;
		draw_arrow(game, angle, color, center);
		i++;
	}
}

static float	normalize_angle(float angle)
{
	while (angle < 0)
		angle += 2 * PI;
	while (angle >= 2 * PI)
		angle -= 2 * PI;
	return (angle);
}

void	draw_compass(t_game *game)
{
	int		cx;
	int		cy;
	float	angle_nord;

	cx = WIDTH - CROSS_SIZE - 20;
	cy = CROSS_SIZE + 20;
	angle_nord = normalize_angle(3 * PI - game->player.angle);
	draw_compass_arrows(game, cx, cy, angle_nord);
}
