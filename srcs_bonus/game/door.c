/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:37:06 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/14 17:34:08 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	load_door_texture(t_game *game)
{
	game->imgs.door.img = mlx_xpm_file_to_image(game->mlx, PATH_DOOR,
			&game->imgs.door.width, &game->imgs.door.height);
	if (!game->imgs.door.img)
		return (print_error("Error: Failed to load door texture", 1));
	game->imgs.door.addr = mlx_get_data_addr(game->imgs.door.img,
			&game->imgs.door.bits_per_pixel,
			&game->imgs.door.line_length,
			&game->imgs.door.endian);
	if (!game->imgs.door.addr || game->imgs.door.line_length <= 0
		|| game->imgs.door.bits_per_pixel <= 0)
		return (print_error("Error: Failed to configure door image", 1));
	return (0);
}

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

t_door	*door_at(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->door_count)
	{
		if (game->doors[i].x == x && game->doors[i].y == y)
			return (&game->doors[i]);
		i++;
	}
	return (NULL);
}

void	toggle_door_at(t_game *game, int x, int y)
{
	t_door	*door;

	door = door_at(game, x, y);
	if (door)
	{
		if (door->is_open == 0)
			door->is_open = 1;
		else
			door->is_open = 0;
	}
}

void	handle_door_interaction(t_game *game)
{
	int	px;
	int	py;

	px = (int)(game->player.x / game->tile_size);
	py = (int)(game->player.y / game->tile_size);
	toggle_door_at(game, px + 1, py);
	toggle_door_at(game, px - 1, py);
	toggle_door_at(game, px, py + 1);
	toggle_door_at(game, px, py - 1);
}
