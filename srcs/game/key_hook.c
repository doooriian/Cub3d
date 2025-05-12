#include "cub3d.h"

static void	update_player(t_game *game)
{
	float		cos_angle;
	float		sin_angle;
	t_player	*player;

	player = &game->player;
	rotate_player(player);
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	move_player(game, cos_angle, sin_angle, game->tile_size);
	reset_player_var(player);
}

int	loop(t_game *game)
{
	if (game->debug)
		display_fps(&game->fps);
	update_player(game);
	update_minimap_loop(game);
	render_walls(game);
	mlx_put_image_to_window(game->mlx, game->win, game->imgs.base.img, 0, 0);
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == ESC)
		ft_exit(game);
	if (keycode == W)
		game->player.go_up = true;
	if (keycode == S)
		game->player.go_down = true;
	if (keycode == A)
		game->player.go_left = true;
	if (keycode == D)
		game->player.go_right = true;
	if (keycode == LEFT)
		game->player.rotate_left = true;
	if (keycode == RIGHT)
		game->player.rotate_right = true;
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->go_up = false;
	if (keycode == S)
		player->go_down = false;
	if (keycode == A)
		player->go_left = false;
	if (keycode == D)
		player->go_right = false;
	if (keycode == LEFT)
		player->rotate_left = false;
	if (keycode == RIGHT)
		player->rotate_right = false;
	return (0);
}
