/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:55:43 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/08 14:21:36 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	game->map_data.map = get_map(argv[1]);
	if (!game->map_data.map)
		return (print_error("Error: Failed to read map", 1));
	if (!init_config(game))
	{
		free_map(game->map_data.map);
		free(game);
		return (print_error("Error: Invalid map configuration", 1));
	}

	if (!init_map(game))
	{
		free_map(game->map_data.map);
		free(game);
		return (print_error("Error: Invalid map", 1));
	}

	// PRINT MAP
	print_map(game->map_data.map);
	print_config(game);

	free_map(game->map_data.map);
	free_tx(game);
	free(game);
	return (0);
}
