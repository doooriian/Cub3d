/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:55:43 by rcaillie          #+#    #+#             */
/*   Updated: 2025/04/23 15:55:43 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

static void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->map_info.width = WIN_WIDTH;
	game->map_info.height = WIN_HEIGHT;
	game->map_info.map = NULL;
	game->player.pos.x = 0;
	game->player.pos.y = 0;
	game->player.dir = 0;
}

int	main(int argc, char **argv)
{
	char	**map;

	if (argc != 2)
		return (print_error("Error: Invalid arguments", 1));
	if (!check_extension(argv[1]))
		return (print_error("Error: Expected .cub extension", 1));
	map = get_map(argv[1]);
	if (!map)
		return (print_error("Error: Failed to read map", 1));
	print_map(map);
	free_map(map);
	printf("Map loaded successfully\n");
	return (0);
}
