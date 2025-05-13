/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 22:59:49 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/13 22:59:49 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	render_minimap_tile(t_game *game, int i, int j)
{
	int	x;
	int	y;

	x = j * game->tile_size + game->map_offset_x;
	y = i * game->tile_size + game->map_offset_y;
	if (game->map_data.map[i][j] == '1')
		draw_square(&game->imgs.map, (t_point){x, y},
			game->tile_size, 0x00888888);
	else if (game->map_data.map[i][j] == '0'
			|| is_char_player(game->map_data.map[i][j]))
		draw_square(&game->imgs.map, (t_point){x, y},
			game->tile_size, 0xFFFFFF);
	else
		draw_square(&game->imgs.map, (t_point){x, y},
			game->tile_size, 0x000000);
}

void	render_minimap(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			render_minimap_tile(game, i, j);
			j++;
		}
		i++;
	}
}

void	render_rays_on_minimap(t_game *game, t_player *player)
{
	int		i;
	int		ray_count;
	float	fraction;
	float	start_angle;

	i = 0;
	ray_count = RAYS;
	fraction = PI / 3 / ray_count;
	start_angle = player->angle - PI / 6;
	while (i < ray_count)
	{
		draw_ray_line(game, player, start_angle);
		start_angle += fraction;
		i++;
	}
}

int	update_minimap_loop(t_game *game)
{
	t_point	pos;

	render_minimap(game);
	if (game->debug)
		render_rays_on_minimap(game, &game->player);
	pos.x = game->player.x - game->player.size / 2 + game->map_offset_x;
	pos.y = game->player.y - game->player.size / 2 + game->map_offset_y;
	draw_square(&game->imgs.map, pos, game->player.size, 0xF7230C);
	mlx_put_image_to_window(game->mlx, game->win_map, game->imgs.map.img, 0, 0);
	return (0);
}
