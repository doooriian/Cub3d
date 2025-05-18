/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doley <doley@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 14:19:41 by doley             #+#    #+#             */
/*   Updated: 2025/05/18 14:19:42 by doley            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
