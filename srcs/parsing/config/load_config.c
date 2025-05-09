/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:51:56 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/09 18:36:20 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_img	*select_texture(t_game *game, int type)
{
	if (type == 1)
		return (&game->imgs.no);
	else if (type == 2)
		return (&game->imgs.so);
	else if (type == 3)
		return (&game->imgs.we);
	else if (type == 4)
		return (&game->imgs.ea);
	return (NULL);
}

static int	load_texture_image(t_game *game, t_img *img, char *path)
{
	int	width;
	int	height;

	img->img = mlx_xpm_file_to_image(game->mlx, path, &width, &height);
	if (!img->img)
		return (print_error("Error: Failed to load texture image", 0));
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	if (!img->addr)
	{
		mlx_destroy_image(game->mlx, img->img);
		return (print_error("Error: Failed to get texture address", 0));
	}
	return (1);
}

static int	load_texture(t_game *game, int type, char *path)
{
	t_img	*img;

	if (!is_valid_texture_path(path))
		return (print_error("Error: Invalid texture path", 0));
	img = select_texture(game, type);
	if (!img)
		return (0);
	return (load_texture_image(game, img, path));
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
			game->map_data.floor_color_set = 1;
		else
			game->map_data.top_color_set = 1;
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
