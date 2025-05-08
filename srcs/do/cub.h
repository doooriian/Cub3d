#ifndef CUB_H
#define CUB_H

# include "./mlx/mlx.h"
# include <X11/X.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>

# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
#define	WIDTH		800
#define	HEIGHT		600
#define	MAP_WIDTH	15
#define	MAP_HEIGHT	10
#define SPEED		0.5
#define	ANGLE_SPEED	0.03
#define PLAYER_SIZE	10
#define PI 			3.14159265

extern int g_map[MAP_HEIGHT][MAP_WIDTH];

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
	float	tmp_x;
	float	tmp_y;
	float	ray_x;
	float	ray_y;
	float	ray_offset;
	float	angle;
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
	int			map_offset_x;
	int			map_offset_y;
	t_img		img;
	t_player	player;
}	t_data;

int	ft_exit(t_data *data);

// INIT //
void	init_data(t_data *data);
void	init_player(t_player *player);

// PLAYER //
void	reset_player_var(t_player *player);
bool	check_collision_walls(int tmp_x, int tmp_y, int tile_size);
void	rotate_player(t_player *player);
void	move_player(t_player *player, float cos_angle, float sin_angle, int tile_size);

// KEY_HOOK //
int key_press(int keycode, t_data *data);
int key_release(int keycode, t_player *player);

// DRAW //
void	put_pixel(t_img *img, int x, int y, int color);
void	draw_square(t_img *img, int x, int y, int size, int color);
void	draw_map(t_data *data);
int		draw_loop(t_data *data);


#endif
