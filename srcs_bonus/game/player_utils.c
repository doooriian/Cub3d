/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doley <doley@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:03:18 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/14 14:49:00 by doley            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	reset_player_var(t_player *player)
{
	player->tmp_x = player->x;
	player->tmp_y = player->y;
	player->ray_x = player->x;
	player->ray_y = player->y;
}

bool	corner_collision(t_game *game, int i, int j)
{
	if (i < 0 || i >= game->map_height || j < 0 || j >= game->map_width)
		return (1);
	if (game->map_data.map[i][j] == '1')
		return (1);
	return (0);
}
