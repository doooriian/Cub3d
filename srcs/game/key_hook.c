#include "cub3d.h"

int	loop(t_game *data)
{
	// Update the minimap
	update_minimap_loop(data);

	// CHANGE WIN COLOR main
	if (data->player.go_up)
		draw_minimap_square(&data->imgs.base, 0, 0, 100, 0x00FF00);
	else if (data->player.go_down)
		draw_minimap_square(&data->imgs.base, 0, 0, 100, 0xFF0000);
	else if (data->player.go_left)
		draw_minimap_square(&data->imgs.base, 0, 0, 100, 0x0000FF);
	else if (data->player.go_right)
		draw_minimap_square(&data->imgs.base, 0, 0, 100, 0xFFFF00);
	else if (data->player.rotate_left)
		draw_minimap_square(&data->imgs.base, 0, 0, 100, 0xFF00FF);
	else if (data->player.rotate_right)
		draw_minimap_square(&data->imgs.base, 0, 0, 100, 0x00FFFF);
	else
		draw_minimap_square(&data->imgs.base, 0, 0, 100, 0xFFFFFF);
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
