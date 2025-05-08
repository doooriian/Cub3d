/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:54:37 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/08 20:08:59 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(char **map)
{
	size_t	i;

	i = 0;
	if (!map || !*map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	destroy_imgs(t_game *game)
{
	if (!game)
		return;
	if (game->imgs.no.img)
		mlx_destroy_image(game->mlx, game->imgs.no.img);
	if (game->imgs.so.img)
		mlx_destroy_image(game->mlx, game->imgs.so.img);
	if (game->imgs.we.img)
		mlx_destroy_image(game->mlx, game->imgs.we.img);
	if (game->imgs.ea.img)
		mlx_destroy_image(game->mlx, game->imgs.ea.img);
}
int	is_line_empty(const char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}
