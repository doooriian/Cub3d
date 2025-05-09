/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:21:18 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/09 19:08:44 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map(char **map)
{
	int	i;

	printf("\n===== MAP =====\n");
	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
	printf("================\n");
}

void	print_config(t_game *game)
{
	printf("\n===== CONFIGURATION =====\n");
	printf("Ceiling color: R:%d, G:%d, B:%d\n", game->map_data.top_color[0],
		game->map_data.top_color[1], game->map_data.top_color[2]);
	printf("Floor color:   R:%d, G:%d, B:%d\n", game->map_data.floor_color[0],
		game->map_data.floor_color[1], game->map_data.floor_color[2]);
	printf("==========================\n");
}

void	print_player(t_player *player)
{
	printf("\n===== PLAYER =====\n");
	printf("Position: X:%.2f, Y:%.2f\n", player->x, player->y);
	printf("Angle: %.2f\n", player->angle);
	printf("Ray X: %.2f, Ray Y: %.2f\n", player->ray_x, player->ray_y);
	printf("Temporary Position: X:%.2f, Y:%.2f\n", player->tmp_x, player->tmp_y);
	printf("Ray Offset: %.2f\n", player->ray_offset);
	printf("Movement: Up: %d, Down: %d, Left: %d, Right: %d\n",
		player->go_up, player->go_down, player->go_left, player->go_right);
	printf("Rotation: Left: %d, Right: %d\n",
		player->rotate_left, player->rotate_right);
	printf("===================\n");
}
