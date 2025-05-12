#include "cub3d.h"

int	loop(t_game *data)
{
	if (data->debug)
		display_fps(&data->fps);

	// Update the minimap
	update_minimap_loop(data);

	render_walls(data);
	mlx_put_image_to_window(data->mlx, data->win, data->imgs.base.img, 0, 0);

	return (0);
}

int key_press(int keycode, t_game *data)
{
	if (keycode == ESC)
		ft_exit(data);
	if(keycode == W)
		data->player.go_up = true;
	if(keycode == S)
		data->player.go_down = true;
	if(keycode == A)
		data->player.go_left = true;
	if(keycode == D)
		data->player.go_right = true;
	if(keycode == LEFT)
		data->player.rotate_left = true;
	if(keycode == RIGHT)
		data->player.rotate_right = true;
	return 0;
}

int key_release(int keycode, t_player *player)
{
	if(keycode == W)
		player->go_up = false;
	if(keycode == S)
		player->go_down = false;
	if(keycode == A)
		player->go_left = false;
	if(keycode == D)
		player->go_right = false;
	if(keycode == LEFT)
		player->rotate_left = false;
	if(keycode == RIGHT)
		player->rotate_right = false;
	return 0;
}
