/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doley <doley@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:21:18 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/13 15:00:01 by doley            ###   ########.fr       */
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
	printf("Map dimensions: Width: %d, Height: %d\n", game->map_width,
		game->map_height);
	printf("Tile size: %d\n", game->tile_size);
	printf("Map offset: X:%d, Y:%d\n", game->map_offset_x, game->map_offset_y);
	if (game->debug)
		printf("Debug mode: ON\n");
	else
		printf("Debug mode: OFF\n");
	printf("==========================\n");
}

void	print_player(t_player *player)
{
	printf("\n===== PLAYER =====\n");
	printf("Position: X:%.2f, Y:%.2f\n", player->x, player->y);
	printf("Angle: %.2f\n", player->angle);
	printf("Ray X: %.2f, Ray Y: %.2f\n", player->ray_x, player->ray_y);
	printf("Temporary Position: X:%.2f, Y:%.2f\n", player->tmp_x,
		player->tmp_y);
	printf("Ray Offset: %.2f\n", player->ray_offset);
	printf("Movement: Up: %d, Down: %d, Left: %d, Right: %d\n",
		player->go_up, player->go_down, player->go_left, player->go_right);
	printf("Rotation: Left: %d, Right: %d\n",
		player->rotate_left, player->rotate_right);
	printf("Player size: %d\n", player->size);
	printf("===================\n");
}

void	display_fps(t_fps *fps)
{
	struct timeval	current_time;
	long			elapsed_time;

	gettimeofday(&current_time, NULL);
	fps->frame_count++;
	elapsed_time = (current_time.tv_sec - fps->last_time.tv_sec) * 1000000L
		+ (current_time.tv_usec - fps->last_time.tv_usec);
	if (elapsed_time >= 1000000L)
	{
		fps->fps = fps->frame_count / (elapsed_time / 1000000.0f);
		fps->frame_count = 0;
		fps->last_time = current_time;
		printf("FPS: %.2f\n", fps->fps);
	}
}
