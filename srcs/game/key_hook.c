/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:01:58 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/13 23:01:58 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	draw_compass(game);
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

void	init_hook(t_game *game)
{
	mlx_hook(game->win, KeyPress, KeyPressMask, key_press, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, key_release, &game->player);
	mlx_hook(game->win, ButtonPress, ButtonPressMask, handle_mouse_click, game);
	mlx_hook(game->win, ButtonRelease, ButtonReleaseMask, handle_mouse_release,
		game);
	mlx_hook(game->win, MotionNotify, PointerMotionMask, handle_mouse_move,
		game);
	mlx_hook(game->win, DestroyNotify, StructureNotifyMask, &ft_exit, game);
	mlx_loop_hook(game->mlx, &loop, game);
	mlx_loop(game->mlx);
}
