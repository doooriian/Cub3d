#include "cub.h"

#define	WIDTH		800
#define	HEIGHT		600
#define	MAP_WIDTH	15
#define	MAP_HEIGHT	10
#define SPEED		0.5
#define PLAYER_SIZE	10

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
	float	x;
	float	y;
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
	int			tile_size;
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

	i = 0;
	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			if (map[i][j] == 1)
				draw_square(&data->img, j * data->tile_size, i * data->tile_size, data->tile_size, 0x00888888);
			else
				draw_square(&data->img, j * data->tile_size, i * data->tile_size, data->tile_size, 0xFFFFFF);
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

bool	check_collision_walls(int new_x, int new_y, int tile_size)
{
	int	i;
	int	j;

	i = (int)new_y / tile_size;
	j = (int)new_x / tile_size;
	if (map[i][j] == 1)
		return (0);
	i = (int)(new_y + PLAYER_SIZE - 1) / tile_size;
	j = (int)(new_x + PLAYER_SIZE - 1) / tile_size;
	if (map[i][j] == 1)
		return (0);
	return (1);
}

void	move_player(t_player *player, int tile_size)
{
	float	new_y;
	float	new_x;

	new_y = player->y;
	new_x = player->x;	
	if (player->go_up)
		new_y -= SPEED;
	if (player->go_down)
		new_y += SPEED;
	if (player->go_right)
		new_x += SPEED;
	if (player->go_left)
		new_x -= SPEED;
	if (check_collision_walls((int)new_x, (int)new_y, tile_size))
	{
		player->x = new_x;
		player->y = new_y;
	}
}

int	draw_loop(t_data *data)
{
	t_player	*player;

	player = &data->player;
	move_player(player, data->tile_size);
	draw_map(data);
	draw_square(&data->img, player->x, player->y, PLAYER_SIZE, 0xF7230C);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}

void	init_data(t_data *data)
{
	int	tile_w;
	int	tile_h;

	tile_w = WIDTH / MAP_WIDTH;
	tile_h = HEIGHT / MAP_HEIGHT;
	if (tile_h < tile_w)
		data->tile_size = tile_h;
	else
		data->tile_size = tile_w;
	data->player.x = WIDTH / 2;
	data->player.y = HEIGHT / 2;
}

int	main(void)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	init_data(data);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 800, 600, "Hello world!");
	data->img.img = mlx_new_image(data->mlx, 800, 600);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
	draw_map(data);
	draw_square(&data->img, data->player.x, data->player.y, PLAYER_SIZE, 0xF7230C);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	mlx_hook(data->win, KeyPress, KeyPressMask, key_press, data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, key_release, &data->player);
	mlx_hook(data->win, DestroyNotify, StructureNotifyMask, &ft_exit, data);
	mlx_loop_hook(data->mlx, &draw_loop, data);
	mlx_loop(data->mlx); 
}
