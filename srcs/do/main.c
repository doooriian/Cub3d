#include "cub.h"

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

int	ft_exit(t_data *data)
{
	free(data);
	exit(0);
}

int	main(void)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	init_data(data);
	init_player(&data->player);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 800, 600, "Hello world!");
	data->img.img = mlx_new_image(data->mlx, 800, 600);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
	draw_map(data);
	draw_square(&data->img, data->player.x + data->map_offset_x, data->player.y + data->map_offset_y, PLAYER_SIZE, 0xF7230C);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	mlx_hook(data->win, KeyPress, KeyPressMask, key_press, data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, key_release, &data->player);
	mlx_hook(data->win, DestroyNotify, StructureNotifyMask, &ft_exit, data);
	mlx_loop_hook(data->mlx, &draw_loop, data);
	mlx_loop(data->mlx);
}
