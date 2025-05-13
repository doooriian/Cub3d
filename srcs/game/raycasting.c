#include "cub3d.h"

static	void	init_ray_direction(t_game *game, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.x / (float)game->tile_size - (float)ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - (float)game->player.x / (float)game->tile_size) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.y / (float)game->tile_size - (float)ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - (float)game->player.y / (float)game->tile_size) * ray->delta_dist_y;
	}
}

void init_ray(t_game *game, t_ray *ray, float ray_angle)
{
	ray->ray_angle = ray_angle;

	// Position du joueur
	ray->map_x = (int)(game->player.x / (float)game->tile_size);
	ray->map_y = (int)(game->player.y / (float)game->tile_size);

	// Direction du rayon
	ray->dir_x = cos(ray_angle);
	ray->dir_y = sin(ray_angle);

	// Calcul des distances entre les cases
	ray->delta_dist_x = fabs(1.0 / ray->dir_x);
	ray->delta_dist_y = fabs(1.0 / ray->dir_y);
	init_ray_direction(game, ray);
}

void advance_ray(t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}

void calculate_perpendicular_distance(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	(void)game;
	// ray->perp_wall_dist *= cos(game->player.angle - ray->ray_angle);
}

int perform_dda(t_game *game, t_ray *ray)
{
	int hit = 0;

	while (hit == 0)
	{
		advance_ray(ray);
		hit = game->map_data.map[ray->map_y][ray->map_x] == '1';
	}
	calculate_perpendicular_distance(game, ray);
	return (hit);
}