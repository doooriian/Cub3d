/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:21:18 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/08 14:21:33 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map(char **map)
{
	int	i;

	printf("\n===== MAP =====\n");
	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
	printf("================\n");
}

void	print_config(t_game *game)
{
	printf("\n===== CONFIGURATION =====\n");
	printf("Ceiling color: R:%d, G:%d, B:%d\n", game->map_data.top_color[0],
		game->map_data.top_color[1], game->map_data.top_color[2]);
	printf("Floor color:   R:%d, G:%d, B:%d\n", game->map_data.floor_color[0],
		game->map_data.floor_color[1], game->map_data.floor_color[2]);
	printf("==========================\n");
}
