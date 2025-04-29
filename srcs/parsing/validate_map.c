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

static int	check_border(const char *row)
{
	size_t i;
	for (i = 0; row[i]; i++)
		if (row[i] != '1' && row[i] != ' ')
			return (-1);
	return (0);
}

int	validate_map(t_map map)
{
	size_t i, j;
	size_t prev_len, curr_len, next_len;

	// count rows
	for (prev_len = 0; map[prev_len]; prev_len++)
		;
	if (prev_len < 3)
		return (print_error("Error: Map too small", -1));

	// check each row
	for (i = 0; map[i]; i++)
	{
		curr_len = ft_strlen(map[i]);
		prev_len = (i > 0) ? ft_strlen(map[i - 1]) : 0;
		next_len = (map[i + 1]) ? ft_strlen(map[i + 1]) : 0;

		// top or bottom border
		if (i == 0 || map[i + 1] == NULL)
		{
			if (check_border(map[i]) < 0)
				return (print_error("Error: Map not closed at border", -1));
			continue;
		}

		// side walls
		if (curr_len < 1 || map[i][0] != '1' || map[i][curr_len - 1] != '1')
			return (print_error("Error: Map side not closed", -1));

		// extended rows
		for (j = 0; j < curr_len; j++)
		{
			if (map[i][j] == ' ')
			{
				if ((j >= prev_len || map[i - 1][j] == ' ') &&
					(j >= next_len || map[i + 1][j] == ' '))
					return (print_error("Error: Invalid hole at row", -1));
			}
		}
	}
	return (0);
}
