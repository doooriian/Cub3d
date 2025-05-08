#include "cub3d.h"

void	reset_player_var(t_player *player)
{
	player->tmp_x = player->x;
	player->tmp_y = player->y;
	player->ray_x = player->x;
	player->ray_y = player->y;
}

bool	check_collision_walls(t_game *game, int tmp_x, int tmp_y, int tile_size)
{
	int	i;
	int	j;

	i = (int)(tmp_y) / tile_size;
	j = (int)(tmp_x) / tile_size;

	// Vérifiez si les indices sont hors limites
	if (i < 0 || i >= game->map_height || j < 0 || j >= game->map_width)
		return (0);

	if (game->map_data.map[i][j] == '1') // Vérifiez les murs avec '1'
		return (0);

	return (1);
}

void	rotate_player(t_player *player)
{
	if (player->rotate_left)
		player->angle -= ANGLE_SPEED;
	if (player->rotate_right)
		player->angle += ANGLE_SPEED;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
}

void	move_player(t_game *game, float cos_angle, float sin_angle, int tile_size)
{
	t_player *player = &game->player;

	if (player->go_up)
	{
		player->tmp_x += cos_angle * SPEED;
		player->tmp_y += sin_angle * SPEED;
	}
	if (player->go_down)
	{
		player->tmp_x -= cos_angle * SPEED;
		player->tmp_y -= sin_angle * SPEED;
	}
	if (player->go_left)
	{
		player->tmp_x += sin_angle * SPEED;
		player->tmp_y -= cos_angle * SPEED;
	}
	if (player->go_right)
	{
		player->tmp_x -= sin_angle * SPEED;
		player->tmp_y += cos_angle * SPEED;
	}
	if (check_collision_walls(game, (int)player->tmp_x, (int)player->tmp_y, tile_size))
	{
		player->x = player->tmp_x;
		player->y = player->tmp_y;
	}
}
