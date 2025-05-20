/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:55:00 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/20 14:15:17 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	parsing(t_game *game, char *path)
{
	game->map_data.map = get_map(path);
	if (!game->map_data.map || game->map_data.map[0] == NULL)
	{
		free(game->map_data.map);
		game->map_data.map = NULL;
		return (print_error("Error: Failed to get map", 1));
	}
	if (!init_config(game))
		ft_exit(game);
	if (!init_map(game))
		ft_exit(game);
	return (0);
}

static t_game	*init_game_win(t_game *game, char *path, bool debug)
{
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return (print_error_void("Error: Memory allocation failure", NULL));
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		print_error("Error: Failed to initialize mlx", 1);
		ft_exit(game);
	}
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!game->win)
	{
		print_error("Error: Failed to create window", 1);
		ft_exit(game);
	}
	game->debug = debug;
	if (parsing(game, path))
		ft_exit(game);
	return (game);
}

static t_game	*init_game(int argc, char **argv)
{
	t_game	*game;
	bool	debug;

	game = NULL;
	debug = false;
	if (argc == 3)
	{
		if (ft_strncmp(argv[2], "-d", 2) == 0)
			debug = true;
		else
			return (print_error_void("Error: Invalid option. Use -d", NULL));
	}
	else if (argc != 2)
		return (print_error_void("Error: ./cub3d <map.cub> [-d]", NULL));
	if (!check_extension(argv[1], ".cub"))
		return (print_error_void("Error: Expected .cub extension", NULL));
	game = init_game_win(game, argv[1], debug);
	return (game);
}

static int	init_sprite(t_game *game)
{
	game->imgs.sprite1.img = mlx_xpm_file_to_image(game->mlx,
			"textures/sprite1.xpm", &game->imgs.sprite1.width,
			&game->imgs.sprite1.height);
	game->imgs.sprite2.img = mlx_xpm_file_to_image(game->mlx,
			"textures/sprite2.xpm", &game->imgs.sprite2.width,
			&game->imgs.sprite2.height);
	game->imgs.sprite3.img = mlx_xpm_file_to_image(game->mlx,
			"textures/sprite3.xpm", &game->imgs.sprite3.width,
			&game->imgs.sprite3.height);
	if (!game->imgs.sprite1.img || !game->imgs.sprite2.img
		|| !game->imgs.sprite3.img)
		return (print_error("Error: Failed to load sprites textures", 0));
	if (!check_img_add(game))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = init_game(argc, argv);
	if (!game)
		ft_exit(game);
	init_data(game);
	if (init_check_door(game))
		ft_exit(game);
	if (game->debug)
	{
		print_config(game);
		print_map(game->map_data.map);
		print_player(&game->player);
	}
	if (init_base_img(game))
		ft_exit(game);
	if (minimap_init(game))
		ft_exit(game);
	find_sprite(game);
	if (!init_sprite(game))
		ft_exit(game);
	init_hook(game);
	ft_exit(game);
	return (0);
}
