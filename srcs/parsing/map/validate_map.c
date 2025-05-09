/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:55:53 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/08 21:48:23 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	has_single_player_start(char **map)
{
	size_t	i;
	size_t	j;
	int		player_count;

	player_count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
				player_count++;
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (print_error("Error: Invalid number of player starts", 0));
	return (1);
}

int	is_valid_map(char **map)
{
	if (!validate_horizontal(map))
		return (0);
	if (!has_single_player_start(map))
		return (0);
	if (!has_invalid_spaces(map))
		return (0);
	return (1);
}
