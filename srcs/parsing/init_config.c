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

static int	is_valid_color(t_game *game, const char *color, int is_top)
{
	int		tab[3];
	char	**rgb_values;

	rgb_values = ft_split(color, ',');
	if (!rgb_values)
		return (0);
	if (ft_tablen(rgb_values) != 3)
	{
		ft_free_tab(rgb_values);
		return (0);
	}
	tab[0] = ft_atoi(rgb_values[0]);
	tab[1] = ft_atoi(rgb_values[1]);
	tab[2] = ft_atoi(rgb_values[2]);
	if (tab[0] < 0 || tab[0] > 255 || tab[1] < 0 || tab[1] > 255 || tab[2] < 0 || tab[2] > 255)
	{
		ft_free_tab(rgb_values);
		return (0);
	}
	if (is_top)
		ft_memcpy(game->map_info.top_color, tab, sizeof(tab));
	else
		ft_memcpy(game->map_info.floor_color, tab, sizeof(tab));
	ft_free_tab(rgb_values);
	return (1);
}

static int	check_all_config_present(t_game *game)
{
	if (!game->tx.no || !game->tx.so || !game->tx.we || !game->tx.ea)
		return (0);
	if (game->map_info.floor_color[0] == -1
		|| game->map_info.top_color[0] == -1)
		return (0);
	return (1);
}

/**
 * @brief Check if the line starts with the given prefix.
 * return 1 if the line starts with the prefix, 0 otherwise.
 */
int	start_with(char *line, const char *prefix)
{
	if (!line || !prefix)
		return (0);
	while (*line && *prefix && *line == *prefix)
	{
		line++;
		prefix++;
	}
	if (*prefix == '\0')
		return (1);
	return (0);
}

/**
 * @brief Check if the line contains a valid name configuration.
 * NO <path> : 1
 * SO <path> : 2
 * WE <path> : 3
 * EA <path> : 4
 * F <color> : 5
 * C <color> : 6
 * ERROR : 0
 *
 * @param line The line to check.
 */
int	check_name_config(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	if (start_with(line, "NO "))
		return (1);
	else if (start_with(line, "SO "))
		return (2);
	else if (start_with(line, "WE "))
		return (3);
	else if (start_with(line, "EA "))
		return (4);
	else if (start_with(line, "F "))
		return (5);
	else if (start_with(line, "C "))
		return (6);
	return (0);
}

/*
** Extrait le chemin après le premier espace sans utiliser de boucle explicite
*/
static char	*extract_path(char *line)
{
	char	*space;
	char	*substr;

	space = ft_strchr(line, ' ');
	if (!space)
		return (NULL);
	substr = ft_substr(line, (space - line) + 1, ft_strlen(space + 1));
	return (substr);
}

// Charge la configuration selon le type
static int	load_config(t_game *game, int type, char *path)
{
	if (type >= 1 && type <= 4)
	{
		if (!is_valid_texture_path(path))
			return (0);
		if (type == 1)
			game->tx.no = mlx_load_png(path);
		else if (type == 2)
			game->tx.so = mlx_load_png(path);
		else if (type == 3)
			game->tx.we = mlx_load_png(path);
		else if (type == 4)
			game->tx.ea = mlx_load_png(path);
	}
	else if (type == 5 || type == 6)
	{
		if (!is_valid_color(game, path, type == 6))
			return (0);
		if (type == 5)
			game->map_info.floor_color[0] = 1;
		else
			game->map_info.top_color[0] = 1;
	}
	else
		return (0);
	return (1);
}

int	check_load_texture(t_game *game, char *line)
{
	int		type;
	char	*path;

	path = extract_path(line);
	if (!path)
		return (0);
	type = check_name_config(line);
	if (!load_config(game, type, path))
	{
		free(path);
		return (0);
	}
	free(path);
	return (1);
}

static int	get_config(t_game *game)
{
	int	i;

	i = 0;
	while (game->map_info.map[i])
	{
		if (check_load_texture(game, game->map_info.map[i]) == 0)
		{
			game->map_info.index = i;
			break ;
		}
		i++;
	}
	if (!check_all_config_present(game))
	{
		ft_putstr_fd("Error: Missing configuration\n", 2);
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
