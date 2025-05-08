
#include "cub3d.h"

int	g_map[MAP_HEIGHT][MAP_WIDTH] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

int	ft_exit(t_game *data)
{
	free(data);
	exit(0);
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

	// GET MLX
	init_data(game);
	init_player(&game->player);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 800, 600, "Hello world!");
	game->img.img = mlx_new_image(game->mlx, 800, 600);
	game->img.img = mlx_new_image(game->mlx, 800, 600);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel, &game->img.line_length, &game->img.endian);
	draw_map(game);
	draw_square(&game->img, game->player.x + game->map_offset_x, game->player.y + game->map_offset_y, PLAYER_SIZE, 0xF7230C);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);



	mlx_hook(game->win, KeyPress, KeyPressMask, key_press, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, key_release, &game->player);
	mlx_hook(game->win, DestroyNotify, StructureNotifyMask, &ft_exit, game);
	mlx_loop_hook(game->mlx, &draw_loop, game);
	mlx_loop(game->mlx);

	// GET MAP
	// game->map_data.map = get_map(argv[1]);
	// if (!game->map_data.map)
	// 	return (print_error("Error: Failed to read map", 1));
	// if (!init_config(game))
	// {
	// 	free_map(game->map_data.map);
	// 	free(game);
	// 	return (print_error("Error: Invalid map configuration", 1));
	// }
	// if (!init_map(game))
	// {
	// 	free_map(game->map_data.map);
	// 	free(game);
	// 	return (print_error("Error: Invalid map", 1));
	// }

	// // PRINT MAP
	// print_map(game->map_data.map);
	// print_config(game);

	// free_map(game->map_data.map);
	// free_tx(game);


	if (game->mlx && game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free(game);
	return (0);
}
