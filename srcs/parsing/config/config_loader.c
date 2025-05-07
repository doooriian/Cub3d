/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_loader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:37:58 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/07 18:37:58 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static int	ft_str_isdigit(const char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

static int	is_valid_color(t_game *game, const char *color, int is_top)
{
	int		tab[3];
	char	**rgb_values;
	char	*trimmed;
	int		i;

	rgb_values = ft_split(color, ',');
	if (!rgb_values || ft_tablen(rgb_values) != 3)
		return (ft_free_tab(rgb_values), 0);
	i = 0;
	while (i < 3)
	{
		trimmed = ft_strtrim(rgb_values[i], " \t");
		if (!trimmed)
			return (ft_free_tab(rgb_values), 0);
		if (!ft_str_isdigit(trimmed)) // -> à créer si besoin
			return (free(trimmed), ft_free_tab(rgb_values), 0);
		tab[i] = ft_atoi(trimmed);
		free(trimmed);
		if (tab[i] < 0 || tab[i] > 255)
			return (ft_free_tab(rgb_values), 0);
		i++;
	}
	if (is_top)
		ft_memcpy(game->map_info.top_color, tab, sizeof(tab));
	else
		ft_memcpy(game->map_info.floor_color, tab, sizeof(tab));
	ft_free_tab(rgb_values);
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

int	load_config(t_game *game, int type, char *path)
{
	void	*img;

	if (type >= 1 && type <= 4)
	{
		if (!is_valid_texture_path(path))
		{
			ft_putstr_fd("Error: Invalid texture path\n", 2);
			return (0);
		}
		img = mlx_load_png(path);
		if (!img)
		{
			ft_putstr_fd("Error: Failed to load texture image\n", 2);
			return (0);
		}
		if (type == 1)
			game->tx.no = img;
		else if (type == 2)
			game->tx.so = img;
		else if (type == 3)
			game->tx.we = img;
		else if (type == 4)
			game->tx.ea = img;
	}
	else if (type == 5 || type == 6)
	{
		if (!is_valid_color(game, path, type == 6))
			return (0);
		if (type == 5)
			game->map_info.floor_color_set = 1;
		else
			game->map_info.top_color_set = 1;
	}
	else
		return (0);
	return (1);
}
