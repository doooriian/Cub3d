/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:20:16 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/08 12:24:09 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
Horizontal check : check for each line if the characters are valid characters "01NSEW ".
In case of space, check if the character preceding the space is a 1,
and if the next character following the space string is a 1 or the end of line.
So it is possible to have space holes in a map provided that this hole is surrounded by walls.
*/

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == '2' || c == 'N' || c == 'E'
		|| c == 'S' || c == 'W' || c == ' ');
}

int	is_valid_map_line(const char *line)
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
