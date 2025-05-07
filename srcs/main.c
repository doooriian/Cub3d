/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:55:43 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/07 14:04:21 by rcaillie         ###   ########.fr       */
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
	printf("Ceiling color: R:%d, G:%d, B:%d\n", game->map_info.top_color[0],
		game->map_info.top_color[1], game->map_info.top_color[2]);
	printf("Floor color:   R:%d, G:%d, B:%d\n", game->map_info.floor_color[0],
		game->map_info.floor_color[1], game->map_info.floor_color[2]);
	printf("==========================\n");
}

int	main(int argc, char **argv)
{
	t_game		*game;

	if (argc != 2)
		return (print_error("Error: Invalid arguments", 1));
	if (!check_extension(argv[1], ".cub"))
		return (print_error("Error: Expected .cub extension", 1));
	game = (t_game *)calloc(1, sizeof(t_game));
	if (!game)
		return (print_error("Error: Memory allocation failed", 1));
	game->map_info.map = get_map(argv[1]);
	if (!game->map_info.map)
		return (print_error("Error: Failed to read map", 1));
	if (!init_config(game))
	{
		free_map(game->map_info.map);
		free(game);
		return (print_error("Error: Invalid map configuration", 1));
	}

	if (!init_map(game))
	{
		free_map(game->map_info.map);
		free(game);
		return (print_error("Error: Invalid map", 1));
	}

	// PRINT MAP
	print_map(game->map_info.map);
	print_config(game);

	free_map(game->map_info.map);
	free_tx(game);
	free(game);
	return (0);
}
