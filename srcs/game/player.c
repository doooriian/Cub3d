#include "cub3d.h"

void	reset_player_var(t_player *player)
{
	player->tmp_x = player->x;
	player->tmp_y = player->y;
	player->ray_x = player->x;
	player->ray_y = player->y;
}

static bool	corner_collision(t_game *game, int i, int j)
{
	if (i < 0 || i >= game->map_height || j < 0 || j >= game->map_width)
		return (1);
	if (game->map_data.map[i][j] == '1')
		return (1);
	return (0);
}

static bool	check_collision(t_game *game, int tmp_x, int tmp_y, int tile_size)
{
	if (corner_collision(game, (int)(tmp_y - game->player.size / 2) / tile_size,
		(int)(tmp_x - game->player.size / 2) / tile_size) == 1)
		return (1);
	if (corner_collision(game, (int)(tmp_y - game->player.size / 2) / tile_size,
		(int)(tmp_x + game->player.size / 2 - 1) / tile_size) == 1)
		return (1);
	if (corner_collision(game, (int)(tmp_y + game->player.size / 2 - 1) / tile_size,
		(int)(tmp_x - game->player.size / 2) / tile_size) == 1)
		return (1);
	if (corner_collision(game, (int)(tmp_y + game->player.size / 2 - 1) / tile_size,
		(int)(tmp_x + game->player.size / 2 - 1) / tile_size) == 1)
		return (1);
	return (0);
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

static void	add_move(t_game *game, float cos_angle, float sin_angle, int mv)
{
	float	*tmp_x;
	float	*tmp_y;

	tmp_x = &game->player.tmp_x;
	tmp_y = &game->player.tmp_y;
	if (mv == 1)
	{
		*tmp_x += cos_angle * SPEED;
		*tmp_y += sin_angle * SPEED;
	}
	if (mv == 2)
	{
		*tmp_x -= cos_angle * SPEED;
		*tmp_y -= sin_angle * SPEED;
	}
	if (mv == 3)
	{
		*tmp_x += sin_angle * SPEED;
		*tmp_y -= cos_angle * SPEED;
	}
	if (mv == 4)
	{
		*tmp_x -= sin_angle * SPEED;
		*tmp_y += cos_angle * SPEED;
	}
}

void	move_player(t_game *game, float cos_angle, float sin_angle, int tile_s)
{
	if (game->player.go_up)
		add_move(game, cos_angle, sin_angle, 1);
	if (game->player.go_down)
		add_move(game, cos_angle, sin_angle, 2);
	if (game->player.go_left)
		add_move(game, cos_angle, sin_angle, 3);
	if (game->player.go_right)
		add_move(game, cos_angle, sin_angle, 4);
	if (!check_collision(game, game->player.tmp_x, game->player.tmp_y, tile_s))
	{
		game->player.x = game->player.tmp_x;
		game->player.y = game->player.tmp_y;
		return ;
	}
	if (!check_collision(game, game->player.tmp_x, game->player.y, tile_s))
		game->player.x = game->player.tmp_x;
	if (!check_collision(game, game->player.x, game->player.tmp_y, tile_s))
		game->player.y = game->player.tmp_y;
}
