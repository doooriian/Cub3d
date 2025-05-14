/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doley <doley@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 21:11:28 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/14 15:14:38 by doley            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
}
