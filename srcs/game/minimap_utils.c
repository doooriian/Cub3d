/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 21:13:59 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/12 21:13:59 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	pos.x = game->player.x - PLAYER_SIZE / 2 + game->map_offset_x;
	pos.y = game->player.y - PLAYER_SIZE / 2 + game->map_offset_y;
	draw_square(&game->imgs.map, pos, PLAYER_SIZE, 0xF7230C);
	mlx_put_image_to_window(game->mlx, game->win_map, game->imgs.map.img, 0, 0);
	return (0);
}

int	is_char_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}
