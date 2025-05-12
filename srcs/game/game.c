#include "cub3d.h"


void init_ray(t_game *game, t_ray *ray, float ray_angle)
{
	int		tile_size = game->tile_size;

	ray->ray_angle = ray_angle;

	// Position du joueur
	ray->map_x = (int)(game->player.x / tile_size);
	ray->map_y = (int)(game->player.y / tile_size);

	// Direction du rayon
	ray->dir_x = cos(ray_angle);
	ray->dir_y = sin(ray_angle);

	// Calcul des distances entre les cases
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);

	// Initialisation des distances pour les premières intersections
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.x / tile_size - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.x / tile_size) * ray->delta_dist_x;
	}

	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.y / tile_size - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.y / tile_size) * ray->delta_dist_y;
	}
}

void	advance_ray(t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->map_x += ray->step_x;
		ray->side = 0; // Vertical
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->map_y += ray->step_y;
		ray->side = 1; // Horizontal
	}
}

int	check_wall_hit(t_game *game, t_ray *ray)
{
	if (game->map_data.map[ray->map_y][ray->map_x] == '1') // '1' = mur
		return (1);
	return (0);
}

void	calculate_perpendicular_distance(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;

	ray->perp_wall_dist *= cos(ray->ray_angle - game->player.angle);
}

int perform_dda(t_game *game, t_ray *ray)
{
	int hit = 0;

	while (hit == 0)
	{
		advance_ray(ray);
		hit = check_wall_hit(game, ray);
	}
	calculate_perpendicular_distance(game, ray);
	return (hit);
}

void	calculate_wall_height(t_game *game, t_ray *ray)
{
	int	line_height;

	// Calculer la hauteur de la ligne à dessiner sur l'écran
	line_height = (int)(HEIGHT / ray->perp_wall_dist);

	// Calculer les pixels les plus bas et les plus hauts à remplir dans la bande actuelle
	game->draw_start = -line_height / 2 + HEIGHT / 2;
	if (game->draw_start < 0)
		game->draw_start = 0;
	game->draw_end = line_height / 2 + HEIGHT / 2;
	if (game->draw_end >= HEIGHT)
		game->draw_end = HEIGHT - 1;
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

void	verLine(t_game *game, int x, int draw_start, int draw_end, int color)
{
	int y;

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


void	draw_wall_tx(t_game *game, t_ray *ray, int x)
{
	double	step;
	double	tex_pos;
	int		line_height;
	int		tex_x;
	int		tex_y;
	int		color;
	int		y;
	double	wall_x;

	line_height = game->draw_end - game->draw_start;
	if (ray->side == 0)
		wall_x = game->player.y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = game->player.x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)TEX_WIDTH);
	if (ray->side == 0 && ray->dir_x > 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	step = 1.0 * TEX_HEIGHT / line_height;
	tex_pos = (game->draw_start - HEIGHT / 2 + line_height / 2) * step;
	y = game->draw_start;
	while (y < game->draw_end)
	{
		tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += step;
		color = get_pixel_color(get_texture(game, ray), tex_x, tex_y);
		draw_pixel(&game->imgs.base, x, y, color);
		y++;
	}
}

void	draw_ceiling(t_game *game, int x)
{
	int ceiling_color;

	ceiling_color = get_rgb_color(game->map_data.top_color[0],
			game->map_data.top_color[1], game->map_data.top_color[2]);
	verLine(game, x, 0, game->draw_start, ceiling_color);
}

void	draw_floor(t_game *game, int x)
{
	int floor_color;

	floor_color = get_rgb_color(game->map_data.floor_color[0],
			game->map_data.floor_color[1], game->map_data.floor_color[2]);
	verLine(game, x, game->draw_end, HEIGHT, floor_color);
}

void	draw_wall_color(t_game *game, t_ray *ray, int x)
{
	int wall_color;

	if (ray->side == 0)
		wall_color = 0xFF0000; // Rouge vertical
	else
		wall_color = 0x00FF00; // Vert horizontal
	verLine(game, x, game->draw_start, game->draw_end, wall_color);
}

void	draw_wall(t_game *game, t_ray *ray, int x)
{
	draw_ceiling(game, x);
	draw_wall_color(game, ray, x);
	// draw_wall_tx(game, ray, x); // Uncomment for textured walls
	draw_floor(game, x);
}

void	render_walls(t_game *game)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIDTH)
	{
		float	ray_angle;

		ray_angle = game->player.angle - (PI / 6) + ((float)x / (float)WIDTH) * (PI / 3);
		init_ray(game, &ray, ray_angle);
		if (perform_dda(game, &ray))
		{
			calculate_wall_height(game, &ray);
			draw_wall(game, &ray, x);
		}
		x++;
	}
}