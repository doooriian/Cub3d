/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compass.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:27:54 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/13 17:11:56 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_arrow(t_game *game, float angle, int color, t_point point)
{
	t_point	tip;
	t_point	base1;
	t_point	base2;

	tip = get_point(angle, CROSS_SIZE, point);
	base1 = get_point(angle + M_PI / 2, BASE_WIDTH, point);
	base2 = get_point(angle - M_PI / 2, BASE_WIDTH, point);
	draw_filled_triangle(game, (t_triangle){tip, base1, base2}, color);
}

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
		angle = base_angle + i * (M_PI / 2);
		if (i == 0)
			color = COLOR_NORTH;
		else
			color = COLOR_OTHER;
		draw_arrow(game, angle, color, center);
		i++;
	}
}

void	draw_compass(t_game *game)
{
	int		cx;
	int		cy;
	float	base_angle;

	cx = WIDTH - CROSS_SIZE - 20;
	cy = CROSS_SIZE + 20;
	base_angle = game->player.angle;
	draw_compass_arrows(game, cx, cy, base_angle);
}
