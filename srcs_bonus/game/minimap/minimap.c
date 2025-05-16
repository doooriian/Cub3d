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

#include "cub3d_bonus.h"

static int	render_minimap_tile_bis(t_game *game, int i, int j)
{
	int		x;
	int		y;
	char	cell;

	x = j * game->tile_size + game->map_offset_x;
	y = i * game->tile_size + game->map_offset_y;
	cell = game->map_data.map[i][j];
	if (cell == 'D')
	{
		if (game->map_doors && game->map_doors[i][j] == '1')
			draw_square(&game->imgs.map, (t_point){x, y},
				game->tile_size, DOOR_COLOR);
		else
			draw_square(&game->imgs.map, (t_point){x, y},
				game->tile_size, DOOR_OPEN_COLOR);
		return (1);
	}
	else if (cell == 'A')
	{
		draw_square(&game->imgs.map, (t_point){x, y},
			game->tile_size, SPRITE_COLOR);
		return (1);
	}
	return (0);
}

static void	render_minimap_tile(t_game *game, int i, int j)
{
	int		x;
	int		y;
	char	cell;

	x = j * game->tile_size + game->map_offset_x;
	y = i * game->tile_size + game->map_offset_y;
	cell = game->map_data.map[i][j];
	if (cell == '1')
		draw_square(&game->imgs.map, (t_point){x, y},
			game->tile_size, WALL_COLOR);
	else if (cell == '0' || is_char_player(cell))
		draw_square(&game->imgs.map, (t_point){x, y},
			game->tile_size, FLOOR_COLOR);
	else if (render_minimap_tile_bis(game, i, j))
		return ;
	else
		draw_square(&game->imgs.map, (t_point){x, y},
			game->tile_size, EMPTY_COLOR);
}

static void	render_rays_on_minimap(t_game *game, t_player *player)
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

int	update_minimap_loop(t_game *game)
{
	t_point	pos;
	char	*fps_text;
	char	*itoa;

	render_minimap(game);
	if (game->debug)
		render_rays_on_minimap(game, &game->player);
	pos.x = game->player.x - game->player.size / 2 + game->map_offset_x;
	pos.y = game->player.y - game->player.size / 2 + game->map_offset_y;
	draw_square(&game->imgs.map, pos, game->player.size, PLAYER_COLOR);
	mlx_put_image_to_window(game->mlx, game->win_map, game->imgs.map.img, 0, 0);
	if (game->debug)
	{
		itoa = ft_itoa((int)game->fps.fps);
		if (!itoa)
			return (1);
		fps_text = ft_strjoin("FPS: ", itoa);
		free(itoa);
		if (!fps_text)
			return (1);
		mlx_string_put(game->mlx, game->win_map, MAP_WIDTH / 2 - 10,
			15, 0xFFFFFF, fps_text);
		free(fps_text);
	}
	return (0);
}
