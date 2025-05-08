/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:41:44 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/08 14:21:13 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
Avoir au moins :
NO <path>
SO <path>
WE <path>
EA <path>
F <color>
C <color>

Pas de doublons
Pas de valeurs vides
Tout doit être présent

Vérifiez que les chemins de texture existent et sont valides

color : R,G,B (0-255)
Vérifiez que les valeurs sont dans la plage valide (0-255)
*/

static int	process_line(t_game *game, char *line, int *seen, int index)
{
	int	type;

	if (is_line_empty(line))
		return (1);
	type = check_name_config(line);
	if (type == 0 || seen[type - 1])
	{
		game->map_data.index = index;
		return (0);
	}
	seen[type - 1] = 1;
	if (!check_load_texture(game, line))
	{
		game->map_data.index = index;
		return (0);
	}
	return (1);
}

static int	get_config(t_game *game)
{
	int	i;
	int	seen[6];

	i = 0;
	ft_bzero(seen, sizeof(int) * 6);
	while (game->map_data.map[i])
	{
		if (seen[0] && seen[1] && seen[2] && seen[3] && seen[4] && seen[5])
		{
			game->map_data.index = i;
			break ;
		}
		if (!process_line(game, game->map_data.map[i], seen, i))
			return (0);
		i++;
	}
	return (1);
}

int	validate_config(t_game *game)
{
	if (!check_all_config_present(game))
	{
		ft_putstr_fd("Error: Missing or duplicate configuration\n", 2);
		free_map(game->map_data.map);
		game->map_data.map = NULL;
		return (0);
	}
	return (1);
}

int	init_config(t_game *game)
{
	if (get_config(game) == 0)
	{
		free_map(game->map_data.map);
		game->map_data.map = NULL;
		ft_putstr_fd("Error: Invalid configuration\n", 2);
		return (0);
	}
	if (!game->map_data.map)
		return (0);
	if (validate_config(game) == 0)
		return (0);
	while (game->map_data.map[game->map_data.index])
	{
		if (!is_line_empty(game->map_data.map[game->map_data.index]))
			break ;
		game->map_data.index++;
	}
	if (game->map_data.index == 0)
	{
		ft_putstr_fd("Error: No valid lines found in the map\n", 2);
		return (0);
	}
	return (1);
}
