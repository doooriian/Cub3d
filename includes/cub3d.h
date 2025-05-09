/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:56:04 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/09 10:41:12 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <X11/X.h>
# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"

// Constants
# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define WIDTH		1500
# define HEIGHT		1000
# define SPEED		0.5
# define ANGLE_SPEED	0.03
# define PLAYER_SIZE	10
# define PI 			3.14159265

// Structures
typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_map_data
{
	int		index;
	char	**map;
	int		floor_color[3];
	int		top_color[3];
	int		top_color_set;
	int		floor_color_set;
}	t_map_data;

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

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_imgs
{
	t_img	no;
	t_img	ea;
	t_img	so;
	t_img	we;
	t_img	base;
}	t_imgs;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			tile_size;
	int			map_offset_x;
	int			map_offset_y;
	t_map_data	map_data;
	t_player	player;
	t_imgs		imgs;
	int			map_width; // Largeur de la carte
	int			map_height; // Hauteur de la carte
}	t_game;

// General
int		ft_exit(t_game *data);

// Initialization
void	init_data(t_game *data);
void	init_player(t_player *player);

// Player management
void	reset_player_var(t_player *player);
void	rotate_player(t_player *player);
bool	check_collision_walls(t_game *game, int tmp_x,
			int tmp_y, int tile_size);
void	move_player(t_game *game, float cos_angle,
			float sin_angle, int tile_size);

// Key hooks
int		key_press(int keycode, t_game *data);
int		key_release(int keycode, t_player *player);

// Drawing
void	put_pixel(t_img *img, int x, int y, int color);
void	draw_square(t_img *img, int x, int y, int size, int color);
void	draw_map(t_game *data);
int		draw_loop(t_game *data);

// File utilities
int		check_extension(const char *path, const char *ext);
int		open_file(const char *path);

// Map utilities
char	**get_map(const char *path);
void	free_map(char **map);
int		is_valid_map(char **map);
int		is_line_empty(const char *line);
char	**duplicate_map(char **map);
int		init_map(t_game *game);
int		has_invalid_spaces(char **map);
size_t	get_max_len(char **map);
size_t	get_map_height(char **map);
int		get_pixel_color(t_img *img, int x, int y);

// Error handling
int		print_error(char *msg, int ret);

// Configuration parsing
int		init_config(t_game *game);
int		check_name_config(char *line);
char	*extract_path(char *line);
int		check_all_config_present(t_game *game);
int		check_load_texture(t_game *game, char *line);
int		is_valid_texture_path(const char *path);
int		is_valid_color(t_game *game, const char *color, int is_top);

// Resource management
void	destroy_imgs(t_game *game);
int		ft_free_tab_i(char **tab, int i);

// Printing functions
void	print_map(char **map);
void	print_config(t_game *game);

// Map validation
int		validate_horizontal(char **map);

#endif