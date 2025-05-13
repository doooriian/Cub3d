#include "cub3d.h"

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

void	rotate_mouse(t_player *player, int direction)
{
	if (direction < 0)
		player->angle -= ANGLE_SPEED;
	if (direction > 0)
		player->angle += ANGLE_SPEED;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
}

int	handle_mouse_click(int button, int x, int y, t_game *game)
{
	(void) x;
	(void) y;
	if (button == 1)
		game->mouse_click = true;
	return (0);
}

int	handle_mouse_release(int button, int x, int y, t_game *game)
{
	(void) x;
	(void) y;
	if (button == 1)
		game->mouse_click = false;
	return (0);
}

int	handle_mouse_move(int x, int y, t_game *game)
{
	(void) y;
	if (game->mouse_x == -1)
	{
		game->mouse_x = x;
		return (0);
	}
	if (x > game->mouse_x && x < game->mouse_x + 10)
		return (0);
	if (x < game->mouse_x && x > game->mouse_x - 10)
		return (0);
	if (game->mouse_click == 1)
		rotate_mouse(&game->player, x - game->mouse_x);
	game->mouse_x = x;
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = init_game(argc, argv);
	if (!game)
		ft_exit(game);
	init_data(game);
	init_player(&game->player, game);
	if (game->debug)
	{
		print_config(game);
		print_map(game->map_data.map);
		print_player(&game->player);
	}
	if (init_base_img(game))
		ft_exit(game);
	if (minimap_init(game)) // MINIMAP
		ft_exit(game);
	mlx_hook(game->win, KeyPress, KeyPressMask, key_press, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, key_release, &game->player);
	mlx_hook(game->win, ButtonPress, ButtonPressMask, handle_mouse_click, game);
	mlx_hook(game->win, ButtonRelease, ButtonReleaseMask, handle_mouse_release, game);
	mlx_hook(game->win, MotionNotify, PointerMotionMask, handle_mouse_move, game);
	mlx_hook(game->win, DestroyNotify, StructureNotifyMask, &ft_exit, game);
	mlx_loop_hook(game->mlx, &loop, game);
	mlx_loop(game->mlx);
	ft_exit(game);
	return (0);
}
