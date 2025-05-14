/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_horizontal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doley <doley@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:51:49 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/14 22:21:12 by doley            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'E'
		|| c == 'S' || c == 'W' || c == ' ' || c == 'D'
		|| c == 'A');
}

static int	is_valid_map_line(const char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (!is_valid_char(line[i]) || is_line_empty(line))
			return (0);
		i++;
	}
	return (1);
}

int	validate_horizontal(char **map)
{
	size_t	i;

	i = 0;
	while (map[i])
	{
		if (!is_valid_map_line(map[i]))
			return (print_error("Error: Invalid character in map", 0));
		i++;
	}
	return (1);
}
