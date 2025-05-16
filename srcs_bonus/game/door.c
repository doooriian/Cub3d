/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:37:06 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/16 18:41:18 by rcaillie         ###   ########.fr       */
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

int	init_door_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	game->map_doors = ft_calloc(game->map_height + 1, sizeof(char *));
	if (!game->map_doors)
		return (print_error("Error: Failed to allocate memory for doors", 1));
	while (y < game->map_height)
	{
		game->map_doors[y] = ft_calloc(game->map_width + 1, sizeof(char));
		if (!game->map_doors[y])
		{
			ft_free_tab_i(game->map_doors, y);
			return (print_error("Error: Failed to allocate memory for doors", 1));
		}
		x = 0;
		while (game->map_data.map[y][x])
		{
			if (game->map_data.map[y][x] == 'D')
				game->map_doors[y][x] = '1'; // 1 = fermée
			else
				game->map_doors[y][x] = '0';
			x++;
		}
		y++;
	}
	return (0);
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
		{
			door->is_open = 1;
			if (game->map_doors && game->map_doors[y])
				game->map_doors[y][x] = 'O';
		}
		else
		{
			door->is_open = 0;
			if (game->map_doors && game->map_doors[y])
				game->map_doors[y][x] = '1';
		}
	}
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
	if (game->map_data.map[py] && px > 0 && game->map_data.map[py][px - 1] == 'D')
		toggle_door_at(game, px - 1, py);
	if (game->map_data.map[py + 1] && game->map_data.map[py + 1][px] == 'D')
		toggle_door_at(game, px, py + 1);
	if (py > 0 && game->map_data.map[py - 1] && game->map_data.map[py - 1][px] == 'D')
		toggle_door_at(game, px, py - 1);
}
