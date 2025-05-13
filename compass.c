#include "cub3d.h"

#define CROSS_SIZE 50
#define BASE_WIDTH 10

#define COLOR_NORTH 0xFF0000
#define COLOR_OTHER 0xFFFFFF

static void	swap_points(t_point *a, t_point *b)
{
	t_point	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	fill_scanline(t_game *g, int y, int x0, int x1, int color)
{
	int	tmp;

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
static int	interp_x(t_point p0, t_point p1, int y)
{
	if (p1.y == p0.y)
		return (p0.x);
	return (p0.x + (y - p0.y) * (p1.x - p0.x) / (p1.y - p0.y));
}

// Fill triangle by scanline method
void	draw_filled_triangle(t_game *g, t_point p0, t_point p1, t_point p2, int color)
{
	int	y;
	int	x_a;
	int	x_b;

	if (p1.y < p0.y)
		swap_points(&p0, &p1);
	if (p2.y < p0.y)
		swap_points(&p0, &p2);
	if (p2.y < p1.y)
		swap_points(&p1, &p2);
	y = p0.y;
	while (y <= p2.y)
	{
		if (y < p1.y)
		{
			x_a = interp_x(p0, p2, y);
			x_b = interp_x(p0, p1, y);
		}
		else
		{
			x_a = interp_x(p0, p2, y);
			x_b = interp_x(p1, p2, y);
		}
		fill_scanline(g, y, x_a, x_b, color);
		y++;
	}
}


void	draw_arrow(t_game *game, float angle, int color, t_point point)
{
	t_point	tip = get_point(angle, CROSS_SIZE, point.x, point.y);
	t_point	base1 = get_point(angle + M_PI / 2, BASE_WIDTH, point.x, point.y);
	t_point	base2 = get_point(angle - M_PI / 2, BASE_WIDTH, point.x, point.y);
	draw_filled_triangle(game, tip, base1, base2, color);
}

void	draw_compass(t_game *game)
{
	int		i;
	float	angle;
	int		color;
	float	base_angle;
	int		cx;
	int		cy;

	// Positionner la boussole en haut à droite
	cx = WIDTH - CROSS_SIZE - 20; // Décalage de 20 pixels du bord droit
	cy = CROSS_SIZE + 20;        // Décalage de 20 pixels du bord supérieur
	base_angle = game->player.angle;
	i = 0;
	while (i < 4)
	{
		angle = base_angle + i * (M_PI / 2);
		color = (i == 0) ? COLOR_NORTH : COLOR_OTHER;
		t_point point = {cx, cy};
		draw_arrow(game, angle, color, point);
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