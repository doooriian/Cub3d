/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:54:57 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/13 23:54:57 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rotate_mouse(t_player *player, int direction)
{
	if (direction < 0)
		player->angle -= ANGLE_SPEED;
	if (direction > 0)
		player->angle += ANGLE_SPEED;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
}

int	handle_mouse_click(int button, int x, int y, t_game *game)
{
	(void) x;
	(void) y;
	if (button == 1)
		game->mouse_click = true;
	return (0);
}

int	handle_mouse_release(int button, int x, int y, t_game *game)
{
	(void) x;
	(void) y;
	if (button == 1)
		game->mouse_click = false;
	return (0);
}

int	handle_mouse_move(int x, int y, t_game *game)
{
	(void) y;
	if (game->mouse_x == -1)
	{
		game->mouse_x = x;
		return (0);
	}
	if (x > game->mouse_x && x < game->mouse_x + 10)
		return (0);
	if (x < game->mouse_x && x > game->mouse_x - 10)
		return (0);
	if (game->mouse_click == 1)
		rotate_mouse(&game->player, x - game->mouse_x);
	game->mouse_x = x;
	return (1);
}
