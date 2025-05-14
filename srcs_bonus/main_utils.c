/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doley <doley@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:49:40 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/14 14:50:36 by doley            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	ft_exit(t_game *game)
{
	if (!game)
		exit(0);
	free_map(game->map_data.map);
	destroy_imgs(game);
	if (game->mlx && game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->mlx && game->win_map)
	{
		mlx_destroy_window(game->mlx, game->win_map);
		game->win_map = NULL;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
	if (game)
		free(game);
	exit(0);
}

int	init_base_img(t_game *game)
{
	game->imgs.base.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->imgs.base.img)
		return (print_error("Error: Failed to create image", 1));
	game->imgs.base.addr = mlx_get_data_addr(game->imgs.base.img,
			&game->imgs.base.bits_per_pixel,
			&game->imgs.base.line_length, &game->imgs.base.endian);
	if (!game->imgs.base.addr || game->imgs.base.line_length <= 0
		|| game->imgs.base.bits_per_pixel <= 0)
		return (print_error("Error: Failed to configure image", 1));
	mlx_put_image_to_window(game->mlx, game->win, game->imgs.base.img, 0, 0);
	return (0);
}
