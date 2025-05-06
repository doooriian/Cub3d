#include "cub.h"

#define	WIDTH		800
#define	HEIGHT		600
#define	MAP_WIDTH	15
#define	MAP_HEIGHT	10
#define SPEED		1

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_player
{
	int	x;
	int	y;
	bool	go_up;
	bool	go_down;
	bool	go_left;
	bool	go_right;
	bool	rotate_left;
	bool	rotate_right;
}	t_player;


typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_player	player;
}	t_data;

int	map[MAP_HEIGHT][MAP_WIDTH] = {
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

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_square(t_img *img, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_data *data)
{
	int	i;
	int	j;
	int	tile_size;
	int	tile_w = WIDTH / MAP_WIDTH;
	int	tile_h = HEIGHT / MAP_HEIGHT;

	if (tile_h < tile_w)
		tile_size = tile_h;
	else
		tile_size = tile_w;
	i = 0;
	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			if (map[i][j] == 1)
				draw_square(&data->img, j * tile_size, i * tile_size, tile_size, 0x00888888);
			else
				draw_square(&data->img, j * tile_size, i * tile_size, tile_size, 0xFFFFFF);
			j++;
		}
		i++;
	}
}

int	ft_exit(t_data *data)
{
	free(data);
	exit(0);
}

int key_press(int keycode, t_data *data)
{
    printf("key_press: %d\n", keycode);
	if (keycode == ESC)
		ft_exit(data);
	if(keycode == W)
        data->player.go_up = true;
    if(keycode == S)
        data->player.go_down = true;
    if(keycode == A)
        data->player.go_left = true;
    if(keycode == D)
        data->player.go_right = true;
    if(keycode == LEFT)
        data->player.rotate_left = true;
    if(keycode == RIGHT)
        data->player.rotate_right = true;
    return 0;
}

int key_release(int keycode, t_player *player)
{
	if(keycode == W)
        player->go_up = false;
    if(keycode == S)
        player->go_down = false;
    if(keycode == A)
        player->go_left = false;
    if(keycode == D)
        player->go_right = false;
    if(keycode == LEFT)
        player->rotate_left = false;
    if(keycode == RIGHT)
        player->rotate_right = false;
    return 0;
}

void	move_player(t_player *player)
{
	if (player->go_up)
		player->y -= SPEED;
	if (player->go_down)
		player->y += SPEED;
	if (player->go_right)
		player->x += SPEED;
	if (player->go_left)
		player->x -= SPEED;
}

int	draw_loop(t_data *data)
{
	t_player	*player;

	player = &data->player;
	move_player(player);
	draw_map(data);
	draw_square(&data->img, player->x, player->y, 10, 0xF7230C);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}

int	main(void)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	data->player.x = WIDTH / 2;
	data->player.y = HEIGHT / 2;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 800, 600, "Hello world!");
	data->img.img = mlx_new_image(data->mlx, 800, 600);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
	draw_map(data);
	draw_square(&data->img, data->player.x, data->player.y, 10, 0xF7230C);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	mlx_hook(data->win, KeyPress, KeyPressMask, key_press, data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, key_release, &data->player);
	mlx_hook(data->win, DestroyNotify, StructureNotifyMask, &ft_exit, data);
	mlx_loop_hook(data->mlx, &draw_loop, data);
	mlx_loop(data->mlx); 
}
