/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 21:13:59 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/16 18:33:40 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	minimap_init_2(t_game *game)
{
	game->win_map = mlx_new_window(game->mlx, MAP_WIDTH, MAP_HEIGHT, "Map");
	if (!game->win_map)
	{
		free(game->mlx);
		free(game);
		return (print_error("Error: Failed to create map window", 1));
	}
	game->imgs.map.img = mlx_new_image(game->mlx, MAP_WIDTH, MAP_HEIGHT);
	if (!game->imgs.map.img)
	{
		free(game->mlx);
		free(game);
		return (print_error("Error: Failed to create map image", 1));
	}
	game->imgs.map.addr = mlx_get_data_addr(game->imgs.map.img,
			&game->imgs.map.bits_per_pixel, &game->imgs.map.line_length,
			&game->imgs.map.endian);
	if (!game->imgs.map.addr || game->imgs.map.line_length <= 0
		|| game->imgs.map.bits_per_pixel <= 0)
		return (print_error("Error: Failed to configure map image", 1));
	return (0);
}

int	minimap_init(t_game *game)
{
	t_point	pos;

	if (!game)
		return (1);
	if (minimap_init_2(game))
		return (1);
	render_minimap(game);
	pos.x = game->player.x - game->player.size / 2 + game->map_offset_x;
	pos.y = game->player.y - game->player.size / 2 + game->map_offset_y;
	draw_square(&game->imgs.map, pos, game->player.size, PLAYER_COLOR);
	mlx_put_image_to_window(game->mlx, game->win_map, game->imgs.map.img, 0, 0);
	return (0);
}

bool	is_ray_touching_wall(t_game *game, float ray_x, float ray_y)
{
	int		i;
	int		j;
	char	cell;

	i = (int)ray_y / game->tile_size;
	j = (int)ray_x / game->tile_size;
	cell = game->map_data.map[i][j];
	if (i < 0 || i >= game->map_height || j < 0 || j >= game->map_width)
		return (1);
	if (cell == '1' || cell == 'A')
		return (1);
	if (cell == 'D')
	{
		if (game->map_doors && game->map_doors[i][j] == '1')
			return (1);
	}
	return (0);
}
