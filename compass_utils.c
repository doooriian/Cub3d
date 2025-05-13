#include "cub3d.h"

void	draw_line2(t_game *game, t_point p0, t_point p1, int color)
{
	int	dx = abs(p1.x - p0.x);
	int	dy = abs(p1.y - p0.y);
	int	sx = (p0.x < p1.x) ? 1 : -1;
	int	sy = (p0.y < p1.y) ? 1 : -1;
	int	err = dx - dy;

	while (1)
	{
		draw_pixel(&game->imgs.base, p0.x, p0.y, color);
		if (p0.x == p1.x && p0.y == p1.y)
			break;
		int e2 = 2 * err;
		if (e2 > -dy) { err -= dy; p0.x += sx; }
		if (e2 < dx) { err += dx; p0.y += sy; }
	}
}

void	draw_triangle(t_game *game, t_point p1, t_point p2, t_point p3, int color)
{
	draw_line2(game, p1, p2, color);
	draw_line2(game, p2, p3, color);
	draw_line2(game, p3, p1, color);
}

void	draw_center_circle(t_game *game, int cx, int cy, int radius, int color)
{
	for (int y = -radius; y <= radius; y++)
		for (int x = -radius; x <= radius; x++)
			if ((x * x) + (y * y) <= radius * radius)
				draw_pixel(&game->imgs.base, cx + x, cy + y, color);
}

t_point	get_point(float angle, int length, int cx, int cy)
{
	t_point	p;
	p.x = cx + cos(angle) * length;
	p.y = cy + sin(angle) * length;
	return (p);
}
