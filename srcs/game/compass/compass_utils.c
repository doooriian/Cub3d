/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compass_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:09:55 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/13 16:10:28 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	swap_points(t_point *a, t_point *b)
{
	t_point	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	fill_scanline(t_game *g, int y, t_point x0_x1, int color)
{
	int	tmp;
	int	x0;
	int	x1;

	x0 = x0_x1.x;
	x1 = x0_x1.y;
	if (x0 > x1)
	{
		tmp = x0;
		x0 = x1;
		x1 = tmp;
	}
	while (x0 <= x1)
	{
		draw_pixel(&g->imgs.base, x0, y, color);
		x0++;
	}
}

// Interpolates the x coordinate on the edge (p0,p1) at a given y
int	interp_x(t_point p0, t_point p1, int y)
{
	if (p1.y == p0.y)
		return (p0.x);
	return (p0.x + (y - p0.y) * (p1.x - p0.x) / (p1.y - p0.y));
}

t_point	get_point(float angle, int length, t_point center)
{
	t_point	p;
	float	cos_val;
	float	sin_val;

	cos_val = cos(angle);
	sin_val = sin(angle);
	p.x = center.x + cos_val * length;
	p.y = center.y + sin_val * length;
	return (p);
}
