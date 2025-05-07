/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:27:13 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/07 20:27:13 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**duplicate_map(char **map)
{
	int		i;
	char	**dup_map;

	i = 0;
	while (map[i])
		i++;
	dup_map = malloc(sizeof(char *) * (i + 1));
	if (!dup_map)
		return (NULL);
	i = 0;
	while (map[i])
	{
		dup_map[i] = ft_strdup(map[i]);
		if (!dup_map[i])
			return (NULL);
		i++;
	}
	dup_map[i] = NULL;
	return (dup_map);
}

int	init_map(t_game *game)
{
	char	**map;

	map = duplicate_map(&game->map_info.map[game->map_info.index]);
	if (!map)
		return (0);
	free_map(game->map_info.map);
	game->map_info.map = NULL;
	if (!is_valid_map(map))
	{
		free_map(map);
		return (0);
	}
	game->map_info.map = map;
	game->map_info.index = 0;
	return (1);
}
