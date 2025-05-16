/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doley <doley@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 21:11:28 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/16 14:28:55 by doley            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_map(char **map)
{
	size_t	i;

	i = 0;
	if (!map || !*map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	ft_free_tab_i(char **tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
	return (0);
}

static void	destroy_img_2(t_game *game)
{
	if (game->imgs.map.img)
	{
		mlx_destroy_image(game->mlx, game->imgs.map.img);
		game->imgs.map.img = NULL;
	}
	if (game->imgs.base.img)
	{
		mlx_destroy_image(game->mlx, game->imgs.base.img);
		game->imgs.base.img = NULL;
	}
	if (game->imgs.door.img)
	{
		mlx_destroy_image(game->mlx, game->imgs.door.img);
		game->imgs.door.img = NULL;
	}
}

static void	destroy_sprite_img(t_game *game)
{
	if (game->imgs.sprite1.img)
	{
		mlx_destroy_image(game->mlx, game->imgs.sprite1.img);
		game->imgs.sprite1.img = NULL;
	}
	if (game->imgs.sprite2.img)
	{
		mlx_destroy_image(game->mlx, game->imgs.sprite2.img);
		game->imgs.sprite2.img = NULL;
	}
	if (game->imgs.sprite3.img)
	{
		mlx_destroy_image(game->mlx, game->imgs.sprite3.img);
		game->imgs.sprite3.img = NULL;
	}
}

void	destroy_imgs(t_game *game)
{
	if (!game)
		return ;
	if (game->imgs.no.img)
	{
		mlx_destroy_image(game->mlx, game->imgs.no.img);
		game->imgs.no.img = NULL;
	}
	if (game->imgs.so.img)
	{
		mlx_destroy_image(game->mlx, game->imgs.so.img);
		game->imgs.so.img = NULL;
	}
	if (game->imgs.we.img)
	{
		mlx_destroy_image(game->mlx, game->imgs.we.img);
		game->imgs.we.img = NULL;
	}
	if (game->imgs.ea.img)
	{
		mlx_destroy_image(game->mlx, game->imgs.ea.img);
		game->imgs.ea.img = NULL;
	}
	destroy_img_2(game);
	destroy_sprite_img(game);
}
