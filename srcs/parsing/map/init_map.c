/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:27:13 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/12 21:10:01 by rcaillie         ###   ########.fr       */
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
		{
			ft_free_tab_i(dup_map, i);
			return (NULL);
		}
		i++;
	}
	dup_map[i] = NULL;
	return (dup_map);
}

char	**allocate_normalized_map(char **map, size_t max_len)
{
	char	**normalized;
	size_t	i;

	i = get_map_height(map);
	normalized = ft_calloc(i + 1, sizeof(char *));
	if (!normalized)
	{
		ft_free_tab(map);
		return (NULL);
	}
	i = -1;
	while (map[++i])
	{
		normalized[i] = ft_calloc(max_len + 1, sizeof(char));
		if (!normalized[i])
		{
			ft_free_tab_i(normalized, i);
			ft_free_tab(map);
			return (NULL);
		}
	}
	return (normalized);
}

void	fill_normalized_map(char **normalized, char **map, size_t max_len)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (map[++i])
	{
		j = ft_strlen(map[i]);
		ft_memcpy(normalized[i], map[i], j);
		while (j < max_len)
			normalized[i][j++] = ' ';
	}
	ft_free_tab(map);
}

char	**normalize_map(char **map)
{
	char	**normalized;
	size_t	max_len;

	max_len = get_max_len(map);
	normalized = allocate_normalized_map(map, max_len);
	if (!normalized)
		return (NULL);
	fill_normalized_map(normalized, map, max_len);
	return (normalized);
}

int	init_map(t_game *game)
{
	char	**map;
	char	**normalized;

	if (!game->map_data.map || !game->map_data.map[game->map_data.index])
		return (print_error("Error: Map not found", 0));
	map = duplicate_map(&game->map_data.map[game->map_data.index]);
	if (!map)
		return (print_error("Error: Failed to duplicate map", 0));
	free_map(game->map_data.map);
	game->map_data.map = NULL;
	game->map_data.index = 0;
	normalized = normalize_map(map);
	if (!normalized || !normalized[0])
	{
		free_map(normalized);
		return (print_error("Error: Failed to normalize map", 0));
	}
	if (!is_valid_map(normalized))
	{
		free_map(normalized);
		return (0);
	}
	game->map_data.map = normalized;
	return (1);
}
