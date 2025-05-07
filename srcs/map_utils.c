/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:54:37 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/07 13:09:43 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(char **map)
{
	size_t	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_img(t_game *game)
{
	if (game->img.no)
		mlx_delete_image(game->mlx, game->img.no);
	if (game->img.so)
		mlx_delete_image(game->mlx, game->img.so);
	if (game->img.we)
		mlx_delete_image(game->mlx, game->img.we);
	if (game->img.ea)
		mlx_delete_image(game->mlx, game->img.ea);
}

void	free_tx(t_game *game)
{
	if (game->tx.no)
		mlx_delete_texture(game->tx.no);
	if (game->tx.so)
		mlx_delete_texture(game->tx.so);
	if (game->tx.we)
		mlx_delete_texture(game->tx.we);
	if (game->tx.ea)
		mlx_delete_texture(game->tx.ea);
}
