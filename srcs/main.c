#include "cub3d.h"

static int	parsing(t_game *game, char *path)
{
	game->map_data.map = get_map(path);
	if (!game->map_data.map)
		return (print_error("Error: Failed to read map", 1));
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
	{
		print_error("Error: Memory allocation failure", 1);
		return (NULL);
	}
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		print_error("Error: Failed to initialize mlx", 1);
		return (NULL);
	}
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!game->win)
	{
		print_error("Error: Failed to create window", 1);
		return (NULL);
	}
	game->debug = debug;
	if (parsing(game, path))
	{
		ft_exit(game);
		return (NULL);
	}
	return (game);
}

static t_game	*init_game(int argc, char **argv)
{
	t_game	*game;
	bool	debug;

	game = NULL;
	debug = false;
	if (argc == 3)
		debug = true;
	else if (argc != 2)
	{
		print_error("Error: ./cub3d <map.cub> [debug if more than 2 args]", 1);
		return (NULL);
	}
	if (!check_extension(argv[1], ".cub"))
	{
		print_error("Error: Expected .cub extension", 1);
		return (NULL);
	}
	game = init_game_win(game, argv[1], debug);
	return (game);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = init_game(argc, argv);
	if (!game)
		ft_exit(game);
	init_data(game);
	init_player(&game->player);
	if (game->debug)
	{
		print_config(game);
		print_map(game->map_data.map);
		print_player(&game->player);
	}

	// Create the image main win
	game->imgs.base.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->imgs.base.img)
		return (print_error("Error: Failed to create image", 1));
	game->imgs.base.addr = mlx_get_data_addr(game->imgs.base.img, &game->imgs.base.bits_per_pixel,
			&game->imgs.base.line_length, &game->imgs.base.endian);
	if (!game->imgs.base.addr || game->imgs.base.line_length <= 0 || game->imgs.base.bits_per_pixel <= 0)
		return (print_error("Error: Failed to configure image", 1));
	draw_minimap_square(&game->imgs.base, 0, 0, 100, 0xF7230C);
	mlx_put_image_to_window(game->mlx, game->win, game->imgs.base.img, 0, 0);

	// Mini map
	if (minimap_init(game))
		ft_exit(game);


	mlx_hook(game->win, KeyPress, KeyPressMask, key_press, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, key_release, &game->player);
	mlx_hook(game->win, DestroyNotify, StructureNotifyMask, &ft_exit, game);
	mlx_loop_hook(game->mlx, &loop, game);
	mlx_loop(game->mlx);

	return (0);
}
