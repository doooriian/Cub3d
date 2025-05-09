#include "cub3d.h"

void	reset_player_var(t_player *player)
{
	player->tmp_x = player->x;
	player->tmp_y = player->y;
	player->ray_x = player->x;
	player->ray_y = player->y;
}

bool	check_collision_walls(int tmp_x, int tmp_y, int tile_size)
{
	int	i;
	int	j;

	i = (int)tmp_y / tile_size;
	j = (int)tmp_x / tile_size;
	if (g_map[i][j] == 1)
		return (1);
	i = (int)(tmp_y + PLAYER_SIZE - 1) / tile_size;
	j = (int)(tmp_x + PLAYER_SIZE - 1) / tile_size;
	if (g_map[i][j] == 1)
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

// void	move_player(t_player *player, float cos_angle, float sin_angle, int tile_size)
// {
// 	if (player->go_up)
// 	{
// 		player->tmp_x += cos_angle * SPEED;
// 		player->tmp_y += sin_angle * SPEED;
// 	}
// 	if (player->go_down)
// 	{
// 		player->tmp_x -= cos_angle * SPEED;
// 		player->tmp_y -= sin_angle * SPEED;
// 	}
// 	if (player->go_left)
// 	{
// 		player->tmp_x += sin_angle * SPEED;
// 		player->tmp_y -= cos_angle * SPEED;
// 	}
// 	if (player->go_right)
// 	{
// 		player->tmp_x -= sin_angle * SPEED;
// 		player->tmp_y += cos_angle * SPEED;
// 	}
// 	if (check_collision_walls((int)player->tmp_x, (int)player->tmp_y, tile_size))
// 	{
// 		player->x = player->tmp_x;
// 		player->y = player->tmp_y;
// 	}
// }

static void	add_move(float *tmp_x, float *tmp_y, float cos_angle, float sin_angle, int mv)
{
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

void	move_player(t_player *player, float cos_angle, float sin_angle, int tile_size)
{
	if (player->go_up)
		add_move(&player->tmp_x, &player->tmp_y, cos_angle, sin_angle, 1);
	if (player->go_down)
		add_move(&player->tmp_x, &player->tmp_y, cos_angle, sin_angle, 2);
	if (player->go_left)
		add_move(&player->tmp_x, &player->tmp_y, cos_angle, sin_angle, 3);
	if (player->go_right)
		add_move(&player->tmp_x, &player->tmp_y, cos_angle, sin_angle, 4);
	if (!check_collision_walls(player->tmp_x, player->tmp_y, tile_size))
	{
		player->x = player->tmp_x;
		player->y = player->tmp_y;
		return ;
	}
	if (!check_collision_walls(player->tmp_x, player->y, tile_size))
		player->x = player->tmp_x;
	if (!check_collision_walls(player->x, player->tmp_y, tile_size))
		player->y = player->tmp_y;
}