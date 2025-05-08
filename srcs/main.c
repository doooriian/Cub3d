#include "cub3d.h"

int	ft_exit(t_game *game)
{
	free_map(game->map_data.map);
	destroy_imgs(game);
	if (game->imgs.base.img)
	{
		mlx_destroy_image(game->mlx, game->imgs.base.img);
		game->imgs.base.img = NULL; // Évitez les lectures invalides
	}
	if (game->mlx && game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL; // Évitez les lectures invalides
	}
	if (game->mlx)
	{
		free(game->mlx);
		game->mlx = NULL;
	}
	if (game)
		free(game);
	exit(0);
}

static int	parsing(t_game *game, char *path)
{
	game->map_data.map = get_map(path);
	if (!game->map_data.map)
		return (print_error("Error: Failed to read map", 1));
	if (!init_config(game))
		ft_exit(game);
	if (!init_map(game))
		ft_exit(game);

	// PRINT MAP
	print_map(game->map_data.map);
	print_config(game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		return (print_error("Error: Invalid arguments", 1));
	if (!check_extension(argv[1], ".cub"))
		return (print_error("Error: Expected .cub extension", 1));
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return (print_error("Error: Memory allocation failure", 1));
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 800, 600, "Hello world!");
	if (parsing(game, argv[1]))
		ft_exit(game);

	// Initialisez les dimensions dynamiques de la carte
	init_data(game);
	init_player(&game->player);

	game->imgs.base.img = mlx_new_image(game->mlx, 800, 600);
	game->imgs.base.addr = mlx_get_data_addr(game->imgs.base.img, &game->imgs.base.bits_per_pixel,
			&game->imgs.base.line_length, &game->imgs.base.endian);
	draw_map(game);
	draw_square(&game->imgs.base, game->player.x - PLAYER_SIZE / 2 + game->map_offset_x,
		game->player.y - PLAYER_SIZE / 2 + game->map_offset_y, PLAYER_SIZE, 0xF7230C);
	mlx_put_image_to_window(game->mlx, game->win, game->imgs.base.img, 0, 0);

	mlx_hook(game->win, KeyPress, KeyPressMask, key_press, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, key_release, &game->player);
	mlx_hook(game->win, DestroyNotify, StructureNotifyMask, &ft_exit, game);
	mlx_loop_hook(game->mlx, &draw_loop, game);
	mlx_loop(game->mlx);

	return (0);
}
