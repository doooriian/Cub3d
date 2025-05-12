#include "cub3d.h"

#define CROSS_SIZE 50
#define BASE_WIDTH 10

#define COLOR_NORTH 0xFF0000
#define COLOR_OTHER 0xFFFFFF

void	draw_line2(t_game *game, t_point p0, t_point p1, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(p1.x - p0.x);
	dy = abs(p1.y - p0.y);
	sx = (p0.x < p1.x) ? 1 : -1;
	sy = (p0.y < p1.y) ? 1 : -1;
	err = dx - dy;
	while (1)
	{
		draw_pixel(&game->imgs.base, p0.x, p0.y, color);
		if (p0.x == p1.x && p0.y == p1.y)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			p0.x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			p0.y += sy;
		}
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
	int	x;
	int	y;

	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if ((x * x) + (y * y) <= radius * radius)
				draw_pixel(&game->imgs.base, cx + x, cy + y, color);
			x++;
		}
		y++;
	}
}

static t_point	get_point(float angle, int length, int cx, int cy)
{
	t_point	p;

	p.x = cx + cos(angle) * length;
	p.y = cy + sin(angle) * length;
	return (p);
}

void	draw_arrow(t_game *game, float angle, int color)
{
	t_point	tip;
	t_point	base1;
	t_point	base2;
	int		cx;
	int		cy;
	float	left;
	float	right;

	cx = WIDTH / 2;
	cy = HEIGHT / 2;
	left = angle + M_PI / 2;
	right = angle - M_PI / 2;
	tip = get_point(angle, CROSS_SIZE, cx, cy);
	base1 = get_point(left, BASE_WIDTH, cx, cy);
	base2 = get_point(right, BASE_WIDTH, cx, cy);
	draw_triangle(game, tip, base1, base2, color);
}

void	draw_compass(t_game *game)
{
	int		i;
	float	angle;
	int		color;
	float	base_angle;
	int		cx;
	int		cy;

	cx = WIDTH / 2;
	cy = HEIGHT / 2;
	base_angle = game->player.angle;
	i = 0;
	while (i < 4)
	{
		angle = base_angle + i * (M_PI / 2);
		color = (i == 0) ? COLOR_NORTH : COLOR_OTHER;
		draw_arrow(game, angle, color);
		i++;
	}
	draw_center_circle(game, cx, cy, 13, COLOR_OTHER);
}

// void	update(t_game *game)
// {
// 	mlx_clear_window(game->mlx, game->win);
// 	draw_compass(game);
// }

// int	loop(t_game *game)
// {
// 	game->player_angle -= 0.01;
// 	update(game);
// 	return (0);
// }

// int	main(void)
// {
// 	t_game	game;

// 	game.mlx = mlx_init();
// 	game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "Croix NESO Rotative");
// 	game.player_angle = 0;
// 	mlx_loop_hook(game.mlx, loop, &game);
// 	mlx_loop(game.mlx);
// 	return (0);
// }