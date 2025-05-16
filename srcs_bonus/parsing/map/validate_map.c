/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:55:53 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/16 19:04:44 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	has_too_much_sprites(char **map)
{
	size_t	i;
	size_t	j;
	int		sprites_count;

	sprites_count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'A')
				sprites_count++;
			j++;
		}
		i++;
	}
	if (sprites_count > MAX_SPRITES)
		return (print_error("Error: Invalid number of sprites starts", 0));
	return (1);
}

int	has_single_player_start(char **map)
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
	if (get_max_len(map) > 100 || get_map_height(map) > 100)
		return (print_error("Error : Map too big", 0));
	if (!validate_horizontal(map))
		return (0);
	if (!has_too_much_sprites(map))
		return (0);
	if (!has_single_player_start(map))
		return (0);
	if (!has_invalid_spaces(map))
		return (0);
	return (1);
}
