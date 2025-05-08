/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_config.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:49:53 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/08 14:21:13 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_texture_path(const char *path)
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

static int	ft_str_isdigit(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	parse_rgb_value(char *value, int *tab, int index)
{
	char	*trimmed;

	trimmed = ft_strtrim(value, " ");
	if (!trimmed || !ft_str_isdigit(trimmed))
	{
		free(trimmed);
		return (0);
	}
	tab[index] = ft_atoi(trimmed);
	free(trimmed);
	return (tab[index] >= 0 && tab[index] <= 255);
}

int	is_valid_color(t_game *game, const char *color, int is_top)
{
	int		tab[3];
	char	**rgb_values;
	int		i;

	rgb_values = ft_split(color, ',');
	if (!rgb_values || ft_tablen(rgb_values) != 3)
	{
		ft_free_tab(rgb_values);
		return (0);
	}
	i = -1;
	while (++i < 3)
	{
		if (!parse_rgb_value(rgb_values[i], tab, i))
		{
			ft_free_tab(rgb_values);
			return (0);
		}
	}
	if (is_top)
		ft_memcpy(game->map_data.top_color, tab, sizeof(tab));
	else
		ft_memcpy(game->map_data.floor_color, tab, sizeof(tab));
	ft_free_tab(rgb_values);
	return (1);
}
