/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:06:14 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/08 14:27:09 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
A partir d'un point,si c'est un ' ' space alors check autour de lui,
Si il y a autre chose qu'un '1' ou un ' ' alors return 1
sinon continue de tout parcourir x + 1 x - 1 y + 1 y - 1
*/
/*
 * Check if there are invalid spaces in the map.
 * Invalid spaces are those that are not surrounded by walls (1).
 * Return 1 if there are invalid spaces, 0 otherwise.
 *
*/
int	has_invalid_spaces(char **map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ' && ((j > 0 && map[i][j - 1] != '1')
				|| (map[i][j + 1] && map[i][j + 1] != '1')))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
