/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:06:14 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/16 13:40:47 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	is_cell_properly_enclosed(char **map, size_t y, size_t x)
{
	char	c;

	c = map[y][x];
	if (c == '0' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == 'D'
		|| c == 'A')
	{
		if (y == 0 || x == 0 || !map[y + 1] || !map[y][x + 1])
			return (0);
		if (map[y - 1][x] == ' ' || map[y + 1][x] == ' '
			|| map[y][x - 1] == ' ' || map[y][x + 1] == ' ')
			return (0);
	}
	return (1);
}

int	has_invalid_spaces(char **map)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (!is_cell_properly_enclosed(map, y, x))
				return (print_error("Error: Invalid map is not closed", 0));
			x++;
		}
		y++;
	}
	return (1);
}
