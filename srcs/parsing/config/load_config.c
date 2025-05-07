/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:51:56 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/07 19:51:56 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_texture(t_game *game, int type, char *path)
{
	void	*img;

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
	return (1);
}

static int	load_config(t_game *game, int type, char *path)
{
	if (type >= 1 && type <= 4)
		return (load_texture(game, type, path));
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
