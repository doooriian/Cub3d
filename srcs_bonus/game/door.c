/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:37:06 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/19 21:17:24 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	init_door(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	if (load_door_texture(game))
		return (1);
	while (game->map_data.map[y])
	{
		x = 0;
		while (game->map_data.map[y][x])
		{
			if (game->door_count >= MAX_DOORS)
				return (print_error("Error: Too many doors", 1));
			if (game->map_data.map[y][x] == 'D')
			{
				game->doors[game->door_count].x = x;
				game->doors[game->door_count].y = y;
				game->doors[game->door_count].is_open = 0;
				game->door_count++;
			}
			x++;
		}
		y++;
	}
	return (0);
}

static int	init_door_map_loop(t_game *game, int x, int y)
{
	while (y < game->map_height)
	{
		game->map_doors[y] = ft_calloc(game->map_width + 1, sizeof(char));
		if (!game->map_doors[y])
		{
			ft_free_tab_i(game->map_doors, y);
			ft_putstr_fd("Error: Failed to allocate", 2);
			return (print_error("memory for doors", 1));
		}
		x = 0;
		while (game->map_data.map[y][x])
		{
			if (game->map_data.map[y][x] == 'D')
				game->map_doors[y][x] = '1';
			else
				game->map_doors[y][x] = '0';
			x++;
		}
		y++;
	}
	return (0);
}

int	init_door_map(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	game->map_doors = ft_calloc(game->map_height + 1, sizeof(char *));
	if (!game->map_doors)
		return (print_error("Error: Failed to allocate memory for doors", 1));
	return (init_door_map_loop(game, x, y));
}

int	init_check_door(t_game *game)
{
	if (init_door(game))
		return (1);
	if (init_door_map(game))
	{
		free_map(game->map_doors);
		game->map_doors = NULL;
		return (1);
	}
	if (!game->map_doors)
	{
		free_map(game->map_doors);
		game->map_doors = NULL;
		return (print_error("Error: Failed to allocate memory for doors", 1));
	}
	return (0);
}

void	handle_door_interaction(t_game *game)
{
	int	px;
	int	py;

	px = (int)(game->player.x / game->tile_size);
	py = (int)(game->player.y / game->tile_size);
	if (!game->map_doors)
		return ;
	if (game->map_data.map[py] && game->map_data.map[py][px + 1] == 'D')
		toggle_door_at(game, px + 1, py);
	if (game->map_data.map[py] && px > 0
		&& game->map_data.map[py][px - 1] == 'D')
		toggle_door_at(game, px - 1, py);
	if (game->map_data.map[py + 1] && game->map_data.map[py + 1][px] == 'D')
		toggle_door_at(game, px, py + 1);
	if (py > 0 && game->map_data.map[py - 1]
		&& game->map_data.map[py - 1][px] == 'D')
		toggle_door_at(game, px, py - 1);
}
