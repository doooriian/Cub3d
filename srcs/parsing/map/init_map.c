/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:27:13 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/08 14:27:58 by rcaillie         ###   ########.fr       */
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

static size_t	get_max_len(char **map)
{
	size_t	max_len;
	size_t	i;

	max_len = 0;
	i = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > max_len)
			max_len = ft_strlen(map[i]);
		i++;
	}
	return (max_len);
}

static size_t	get_map_height(char **map)
{
	size_t	height;

	height = 0;
	while (map[height])
		height++;
	return (height);
}

char	**normalize_map(char **map)
{
	char	**normalized;
	size_t	max_len;
	size_t	i;
	size_t	j;

	max_len = get_max_len(map);
	i = get_map_height(map);
	normalized = ft_calloc(i + 1, sizeof(char *));
	if (!normalized)
		return (NULL);
	i = -1;
	while (map[++i])
	{
		normalized[i] = ft_calloc(max_len + 1, sizeof(char));
		if (!normalized[i])
		{
			ft_free_tab_i(normalized, i);
			return (NULL);
		}
		j = ft_strlen(map[i]);
		ft_memcpy(normalized[i], map[i], j);
		while (j < max_len)
			normalized[i][j++] = ' ';
	}
	return (normalized);
}

int	init_map(t_game *game)
{
	char	**map;
	char	**normalized;

	map = duplicate_map(&game->map_data.map[game->map_data.index]);
	if (!map)
		return (0);
	free_map(game->map_data.map);
	game->map_data.map = map;
	game->map_data.index = 0;
	normalized = normalize_map(game->map_data.map);
	if (!normalized)
		return (0);
	print_map(normalized); /// TMP
	if (!is_valid_map(normalized))
	{
		free_map(game->map_data.map);
		game->map_data.map = NULL;
		free_map(normalized);
		return (0);
	}
	return (1);
}
