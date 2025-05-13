/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_filled_triangle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:12:02 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/13 17:09:32 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_filled_triangle_upper(t_game *g, t_triangle tri, int color)
{
	int	y;
	int	x_a;
	int	x_b;

	y = tri.p0.y;
	while (y < tri.p1.y)
	{
		x_a = interp_x(tri.p0, tri.p2, y);
		x_b = interp_x(tri.p0, tri.p1, y);
		fill_scanline(g, y, (t_point){x_a, x_b}, color);
		y++;
	}
}

static void	draw_filled_triangle_lower(t_game *g, t_triangle tri, int color)
{
	int	y;
	int	x_a;
	int	x_b;

	y = tri.p1.y;
	while (y <= tri.p2.y)
	{
		x_a = interp_x(tri.p0, tri.p2, y);
		x_b = interp_x(tri.p1, tri.p2, y);
		fill_scanline(g, y, (t_point){x_a, x_b}, color);
		y++;
	}
}

static void	draw_filled_triangle(t_game *g, t_triangle tri, int color)
{
	if (tri.p1.y < tri.p0.y)
		swap_points(&tri.p0, &tri.p1);
	if (tri.p2.y < tri.p0.y)
		swap_points(&tri.p0, &tri.p2);
	if (tri.p2.y < tri.p1.y)
		swap_points(&tri.p1, &tri.p2);
	draw_filled_triangle_upper(g, tri, color);
	draw_filled_triangle_lower(g, tri, color);
}

void	draw_arrow(t_game *game, float angle, int color, t_point point)
{
	t_point	tip;
	t_point	base1;
	t_point	base2;

	tip = get_point(angle, CROSS_SIZE, point);
	base1 = get_point(angle + PI / 2, BASE_WIDTH, point);
	base2 = get_point(angle - PI / 2, BASE_WIDTH, point);
	draw_filled_triangle(game, (t_triangle){tip, base1, base2}, color);
}
