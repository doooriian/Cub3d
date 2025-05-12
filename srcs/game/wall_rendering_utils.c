#include "cub3d.h"

void calculate_wall_height(t_game *game, t_ray *ray)
{
	int	line_height;

	line_height = (int)(HEIGHT / ray->perp_wall_dist);
	game->draw_start = -line_height / 2 + HEIGHT / 2;
	if (game->draw_start < 0)
		game->draw_start = 0;
	game->draw_end = line_height / 2 + HEIGHT / 2;
	if (game->draw_end >= HEIGHT)
		game->draw_end = HEIGHT - 1;
}

void draw_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= img->line_length / (img->bits_per_pixel / 8)
		|| y < 0 || y >= img->line_length / (img->bits_per_pixel / 8))
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void draw_line(t_game *game, int x, int draw_start, int draw_end, int color)
{
	int y;

	y = draw_start;
	while (y < draw_end)
	{
		draw_pixel(&game->imgs.base, x, y, color);
		y++;
	}
}

t_img *get_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0 && ray->dir_x < 0)
		return (&game->imgs.we);
	if (ray->side == 0 && ray->dir_x >= 0)
		return (&game->imgs.ea);
	if (ray->side == 1 && ray->dir_y < 0)
		return (&game->imgs.no);
	return (&game->imgs.so);
}
