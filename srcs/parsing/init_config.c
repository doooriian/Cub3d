/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_config.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:41:44 by rcaillie          #+#    #+#             */
/*   Updated: 2025/04/29 15:41:44 by rcaillie         ###   ########.fr       */
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

static int	is_valid_texture_path(const char *path)
{
	int	fd;

	fd = open_file(path);
	if (fd < 0)
		return (0);
	close(fd);
	if (check_extension(path, ".png") == 0)
		return (0);
	return (1);
}

static int	is_valid_color(const char *color)
{
	int		red;
	int		green;
	int		blue;
	char	**rgb_values;

	rgb_values = ft_split(color, ',');
	if (!rgb_values)
		return (0);
	if (ft_tablen(rgb_values) != 3)
	{
		ft_free_tab(rgb_values);
		return (0);
	}
	red = ft_atoi(rgb_values[0]);
	green = ft_atoi(rgb_values[1]);
	blue = ft_atoi(rgb_values[2]);
	if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255)
	{
		ft_free_tab(rgb_values);
		return (0);
	}
	ft_free_tab(rgb_values);
	return (1);
}

static int	has_duplicates_or_empty(t_game *game, const char *key)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (game->map_info.map[i])
	{
		if (ft_strnstr(game->map_info.map[i], key, ft_strlen(key)) == game->map_info.map[i])
		{
			if (ft_strlen(game->map_info.map[i]) <= ft_strlen(key))
				return (1); // Valeur vide
			count++;
		}
		i++;
	}
	return (count > 1); // Doublons
}

static int	check_all_config_present(t_game *game)
{
	if (!game->tx.no || !game->tx.so || !game->tx.we || !game->tx.ea)
		return (0);
	if (game->map_info.floor_color[0] == -1 || game->map_info.top_color[0] == -1)
		return (0);
	return (1);
}

static int	get_config(t_game *game)
{
	int	i;

	i = 0;
	while (game->map_info.map[i])
	{
		if (ft_strnstr(game->map_info.map[i], "NO ", 3) == game->map_info.map[i])
			game->tx.no = is_valid_texture_path(game->map_info.map[i] + 3) ? mlx_load_png(game->map_info.map[i] + 3) : NULL;
		else if (ft_strnstr(game->map_info.map[i], "SO ", 3) == game->map_info.map[i])
			game->tx.so = is_valid_texture_path(game->map_info.map[i] + 3) ? mlx_load_png(game->map_info.map[i] + 3) : NULL;
		else if (ft_strnstr(game->map_info.map[i], "WE ", 3) == game->map_info.map[i])
			game->tx.we = is_valid_texture_path(game->map_info.map[i] + 3) ? mlx_load_png(game->map_info.map[i] + 3) : NULL;
		else if (ft_strnstr(game->map_info.map[i], "EA ", 3) == game->map_info.map[i])
			game->tx.ea = is_valid_texture_path(game->map_info.map[i] + 3) ? mlx_load_png(game->map_info.map[i] + 3) : NULL;
		else if (ft_strnstr(game->map_info.map[i], "F ", 2) == game->map_info.map[i])
			game->map_info.floor_color[0] = is_valid_color(game->map_info.map[i] + 2) ? 1 : -1;
		else if (ft_strnstr(game->map_info.map[i], "C ", 2) == game->map_info.map[i])
			game->map_info.top_color[0] = is_valid_color(game->map_info.map[i] + 2) ? 1 : -1;
		i++;
	}
	if (!check_all_config_present(game) || has_duplicates_or_empty(game, "NO ") || has_duplicates_or_empty(game, "SO ")
		|| has_duplicates_or_empty(game, "WE ") || has_duplicates_or_empty(game, "EA ")
		|| has_duplicates_or_empty(game, "F ") || has_duplicates_or_empty(game, "C "))
	{
		free_map(game->map_info.map);
		game->map_info.map = NULL;
		return (0);
	}
	return (1);
}

int	validate_config(t_game *game)
{
	(void)game;
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
	{
		free_map(game->map_info.map);
		return (0);
	}
	return (1);
}