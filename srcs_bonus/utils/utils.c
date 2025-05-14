/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doley <doley@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:46:27 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/14 23:57:33 by doley            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	get_pixel_color(t_img *img, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return (0);
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

int	get_rgb_color(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

double get_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec * 1e-6;
}

void	find_sprite(t_game *game)
{
	int	y = 0;
	int	x = 0;
	while (game->map_data.map[y])
	{
		x = 0;
		while (game->map_data.map[y][x])
		{
			if (game->map_data.map[y][x] == 'A')
			{
				game->sprite_x = x;
				game->sprite_y = y;
			}
			x++;
		}
		y++;
	}
}