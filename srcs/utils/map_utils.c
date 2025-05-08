/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:54:37 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/08 17:16:52 by rcaillie         ###   ########.fr       */
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

void	free_imgs(t_game *game)
{
	if (!game || !game->imgs)
		return;
	if (game->imgs->no)
	{
		if (game->imgs->no->img)
			mlx_destroy_image(game->mlx, game->imgs->no->img);
		free(game->imgs->no);
	}
	if (game->imgs->so)
	{
		if (game->imgs->so->img)
			mlx_destroy_image(game->mlx, game->imgs->so->img);
		free(game->imgs->so);
	}
	if (game->imgs->we)
	{
		if (game->imgs->we->img)
			mlx_destroy_image(game->mlx, game->imgs->we->img);
		free(game->imgs->we);
	}
	if (game->imgs->ea)
	{
		if (game->imgs->ea->img)
			mlx_destroy_image(game->mlx, game->imgs->ea->img);
		free(game->imgs->ea);
	}
	free(game->imgs);
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
