/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:35:54 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/07 18:35:54 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Check if the line starts with the given prefix
 * return 1 if the line starts with the prefix, 0 otherwise
 */
static int	start_with(char *line, const char *prefix)
{
	if (!line || !prefix)
		return (0);
	while (*line && *prefix && *line == *prefix)
	{
		line++;
		prefix++;
	}
	if (*prefix == '\0')
		return (1);
	return (0);
}

/**
 * @brief Check if the line contains a valid name config
 * NO <path> : 1
 * SO <path> : 2
 * WE <path> : 3
 * EA <path> : 4
 * F <color> : 5
 * C <color> : 6
 * ERROR : 0
 *
 * @param line The line to check.
 */
int	check_name_config(char *line)
{
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	if (start_with(line, "NO "))
		return (1);
	else if (start_with(line, "SO "))
		return (2);
	else if (start_with(line, "WE "))
		return (3);
	else if (start_with(line, "EA "))
		return (4);
	else if (start_with(line, "F "))
		return (5);
	else if (start_with(line, "C "))
		return (6);
	return (0);
}

/**
 * @brief Extract the path from the line
 * The path is the part of the line after the first space
 * If there is no path, return NULL
 */
char	*extract_path(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	while (*line && *line != ' ' && *line != '\t')
		line++;
	while (*line == ' ' || *line == '\t')
		line++;
	if (*line == '\0')
		return (NULL);
	return (ft_strdup(line));
}

int	check_all_config_present(t_game *game)
{
	if (!game->tx.no || !game->tx.so || !game->tx.we || !game->tx.ea)
		return (0);
	if (!game->map_info.top_color_set || !game->map_info.floor_color_set)
		return (0);
	return (1);
}
