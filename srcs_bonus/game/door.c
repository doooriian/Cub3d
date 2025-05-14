/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:37:06 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/14 17:05:47 by rcaillie         ###   ########.fr       */
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

int	distance(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

void	handle_door_interaction(t_game *game)
{
	int		i;
	float	px;
	float	py;
	float	dist;

	px = game->player.x / (float)game->tile_size;
	py = game->player.y / (float)game->tile_size;
	i = 0;
	while (i < game->door_count)
	{
		dist = distance(game->player.x, game->player.y, (game->doors[i].x + 0.5)
				* game->tile_size, (game->doors[i].y + 0.5) * game->tile_size);
		if (dist < game->tile_size * 2)
		{
			game->doors[i].is_open = 1;
		}
		else
			game->doors[i].is_open = 0;
		i++;
	}
}
