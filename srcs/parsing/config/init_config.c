/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:41:44 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/07 15:20:09 by rcaillie         ###   ########.fr       */
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

static int	get_config(t_game *game)
{
	int		i;
	int		seen[6];
	int		type;

	i = 0;
	ft_bzero(seen, sizeof(int) * 6);
	while (game->map_info.map[i])
	{
		if (seen[0] && seen[1] && seen[2] && seen[3] && seen[4] && seen[5])
		{
			game->map_info.index = i;
			break ;
		}
		if (game->map_info.map[i][0] == '\t' || game->map_info.map[i][0] == ' '
			|| game->map_info.map[i][0] == '\n' || game->map_info.map[i][0] == '\0')
		{
			i++;
			continue ;
		}
		type = check_name_config(game->map_info.map[i]);
		if (type == 0 || seen[type - 1])
		{
			game->map_info.index = i;
			return (0);
		}
		seen[type - 1] = 1;
		if (!check_load_texture(game, game->map_info.map[i]))
		{
			game->map_info.index = i;
			return (0);
		}
		i++;
	}
	return (1);
}

int	validate_config(t_game *game)
{
	if (!check_all_config_present(game))
	{
		ft_putstr_fd("Error: Missing or duplicate configuration\n", 2);
		free_map(game->map_info.map);
		game->map_info.map = NULL;
		return (0);
	}
	return (1);
}

int	init_config(t_game *game)
{
	if (get_config(game) == 0)
	{
		free_map(game->map_info.map);
		ft_putstr_fd("Error: Invalid configuration\n", 2);
		return (0);
	}
	if (!game->map_info.map)
		return (0);
	if (validate_config(game) == 0)
		return (0);
	return (1);
}
