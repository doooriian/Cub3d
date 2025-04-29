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
	int	red;
	int	green;
	int	blue;
	char	**rgb_values;

	rgb_values = ft_split(color, ',');
	if (!rgb_values)
		return (0);
	if (ft_strarr_len(rgb_values) != 3)
	{
		free_strarr(rgb_values);
		return (0);
	}
	red = ft_atoi(rgb_values[0]);
	green = ft_atoi(rgb_values[1]);
	blue = ft_atoi(rgb_values[2]);
	if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255)
	{
		free_strarr(rgb_values);
		return (0);
	}
	free_strarr(rgb_values);
	return (1);
}