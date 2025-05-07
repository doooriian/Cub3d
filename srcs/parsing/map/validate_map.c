/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:55:53 by rcaillie          #+#    #+#             */
/*   Updated: 2025/04/29 10:55:53 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == '2' || c == 'N' || c == 'E'
		|| c == 'S' || c == 'W' || c == ' ');
}

static int	is_valid_map_line(const char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (!is_valid_char(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_map(char **map)
{
	size_t	i;

	i = 0;
	while (map[i])
	{
		if (!is_valid_map_line(map[i]))
			return (0);
		i++;
	}
	return (1);
}
