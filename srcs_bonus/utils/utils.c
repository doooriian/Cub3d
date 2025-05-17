/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doley <doley@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:46:27 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/17 18:55:10 by doley            ###   ########.fr       */
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

double	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec * 1e-6);
}

void	find_sprite(t_game *game)
{
	int	y;
	int	x;

	game->sprite_count = 0;
	y = 0;
	while (game->map_data.map[y])
	{
		x = 0;
		while (game->map_data.map[y][x])
		{
			if (game->map_data.map[y][x] == 'A'
				&& game->sprite_count < MAX_SPRITES)
			{
				game->sprites[game->sprite_count].x = x;
				game->sprites[game->sprite_count].y = y;
				game->sprites[game->sprite_count].frame = 0;
				game->sprites[game->sprite_count].last_time = get_time();
				game->sprites[game->sprite_count].active = true;
				game->sprite_count++;
			}
			x++;
		}
		y++;
	}
}

int	check_img_add(t_game *game)
{
	game->imgs.sprite1.addr = mlx_get_data_addr(game->imgs.sprite1.img,
			&game->imgs.sprite1.bits_per_pixel,
			&game->imgs.sprite1.line_length, &game->imgs.sprite1.endian);
	if (!game->imgs.sprite1.addr || game->imgs.sprite1.line_length <= 0
		|| game->imgs.sprite1.bits_per_pixel <= 0)
		return (print_error("Error: Failed to configure sprite1 image", 0));
	game->imgs.sprite2.addr = mlx_get_data_addr(game->imgs.sprite2.img,
			&game->imgs.sprite2.bits_per_pixel,
			&game->imgs.sprite2.line_length, &game->imgs.sprite2.endian);
	if (!game->imgs.sprite2.addr || game->imgs.sprite2.line_length <= 0
		|| game->imgs.sprite2.bits_per_pixel <= 0)
		return (print_error("Error: Failed to configure sprite2 image", 0));
	game->imgs.sprite3.addr = mlx_get_data_addr(game->imgs.sprite3.img,
			&game->imgs.sprite3.bits_per_pixel,
			&game->imgs.sprite3.line_length, &game->imgs.sprite3.endian);
	if (!game->imgs.sprite3.addr || game->imgs.sprite3.line_length <= 0
		|| game->imgs.sprite3.bits_per_pixel <= 0)
		return (print_error("Error: Failed to configure sprite3 image", 0));
	return (1);
}
