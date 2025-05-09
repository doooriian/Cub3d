#include "cub3d.h"

int	ft_exit(t_game *game)
{
	free_map(game->map_data.map);
	destroy_imgs(game);
	if (game->imgs.base.img)
	{
		mlx_destroy_image(game->mlx, game->imgs.base.img);
		game->imgs.base.img = NULL;
	}
	if (game->mlx && game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
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

int	minimap_init(t_game *game)
{
	game->win_map = mlx_new_window(game->mlx, MAP_WIDTH, MAP_HEIGHT, "Map");
	if (!game->win_map)
	{
		free(game->mlx);
		free(game);
		return (print_error("Error: Failed to create map window", 1));
	}
	game->imgs.map.img = mlx_new_image(game->mlx, MAP_WIDTH, MAP_HEIGHT);
	if (!game->imgs.map.img)
	{
		free(game->mlx);
		free(game);
		return (print_error("Error: Failed to create map image", 1));
	}
	game->imgs.map.addr = mlx_get_data_addr(game->imgs.map.img, &game->imgs.map.bits_per_pixel,
			&game->imgs.map.line_length, &game->imgs.map.endian);
	if (!game->imgs.map.addr || game->imgs.map.line_length <= 0 || game->imgs.map.bits_per_pixel <= 0)
		return (print_error("Error: Failed to configure map image", 1));

	render_minimap(game);
	draw_minimap_square(&game->imgs.map, game->player.x - PLAYER_SIZE / 2 + game->map_offset_x,
		game->player.y - PLAYER_SIZE / 2 + game->map_offset_y, PLAYER_SIZE, 0xF7230C);
	mlx_put_image_to_window(game->mlx, game->win_map, game->imgs.map.img, 0, 0);
	return (0);
}

int	loop(t_game *data)
{
	// Update the minimap
	update_minimap_loop(data);

	// CHANGE WIN COLOR main
	if (data->player.go_up)
		draw_minimap_square(&data->imgs.base, 0, 0, 100, 0x00FF00);
	else if (data->player.go_down)
		draw_minimap_square(&data->imgs.base, 0, 0, 100, 0xFF0000);
	else if (data->player.go_left)
		draw_minimap_square(&data->imgs.base, 0, 0, 100, 0x0000FF);
	else if (data->player.go_right)
		draw_minimap_square(&data->imgs.base, 0, 0, 100, 0xFFFF00);
	else if (data->player.rotate_left)
		draw_minimap_square(&data->imgs.base, 0, 0, 100, 0xFF00FF);
	else if (data->player.rotate_right)
		draw_minimap_square(&data->imgs.base, 0, 0, 100, 0x00FFFF);
	else
		draw_minimap_square(&data->imgs.base, 0, 0, 100, 0xFFFFFF);
	mlx_put_image_to_window(data->mlx, data->win, data->imgs.base.img, 0, 0);

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
	if (!game->mlx)
	{
		free(game);
		return (print_error("Error: Failed to initialize mlx", 1));
	}
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Hello world!");
	if (!game->win)
	{
		free(game->mlx);
		free(game);
		return (print_error("Error: Failed to create window", 1));
	}
	if (parsing(game, argv[1]))
		ft_exit(game);

	init_data(game);
	init_player(&game->player);

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
	{
		free(game->mlx);
		free(game);
		return (print_error("Error: Failed to initialize minimap", 1));
	}


	mlx_hook(game->win, KeyPress, KeyPressMask, key_press, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, key_release, &game->player);
	mlx_hook(game->win, DestroyNotify, StructureNotifyMask, &ft_exit, game);
	mlx_loop_hook(game->mlx, &loop, game);
	mlx_loop(game->mlx);

	return (0);
}
