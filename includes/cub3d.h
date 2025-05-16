/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:56:04 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/16 18:02:08 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>
# include <stdbool.h>
# include <X11/X.h>
# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"

/* ============== Macros ============== */
/* ==================================== */

// Keys
# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363

// Constants
# define WIDTH		1000
# define HEIGHT		800
# define SPEED		1.5
# define ANGLE_SPEED	0.05
# define PI 		3.14159265

// Minimap
# define MAP_WIDTH	800
# define MAP_HEIGHT	600

// COMPASS
# define CROSS_SIZE 50
# define BASE_WIDTH 10
# define COLOR_NORTH 0xFF0000
# define COLOR_OTHER 0xFFFFFF

/* ============ Structures ============ */
/* ==================================== */

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

// Compass structures
typedef struct s_triangle
{
	t_point	p0;
	t_point	p1;
	t_point	p2;
}	t_triangle;

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
	int		size;
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
	int		height;
	int		width;
}	t_img;

typedef struct s_imgs
{
	t_img	no;
	t_img	ea;
	t_img	so;
	t_img	we;
	t_img	base;
}	t_imgs;

typedef struct s_fps
{
	struct timeval	last_time;
	int				frame_count;
	float			fps;
}	t_fps;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
	float	ray_angle;
	int		side; // 0 : mur vertical, 1 : mur horizontal
}	t_ray;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			tile_size;
	t_map_data	map_data;
	t_player	player;
	t_imgs		imgs;
	int			map_width; // Largeur de la carte
	int			map_height; // Hauteur de la carte
	bool		debug;
	t_fps		fps;
	int			draw_start;
	int			draw_end;
}	t_game;

/* ======== Function Prototypes ======== */
/* ===================================== */

/* Compass */
// Compass
void	draw_compass(t_game *game);

// Compass drawing functions
void	draw_arrow(t_game *game, float angle, int color, t_point point);

// Compass utils
void	swap_points(t_point *a, t_point *b);
void	fill_scanline(t_game *g, int y, t_point x0_x1, int color);
int		interp_x(t_point p0, t_point p1, int y);
t_point	get_point(float angle, int length, t_point center);

/* GAME FUNCTIONS */
// init
void	init_data(t_game *game);

// Key hooks
int		loop(t_game *game);
void	init_hook(t_game *game);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_player *player);
int		handle_mouse_click(int button, int x, int y, t_game *game);
int		handle_mouse_release(int button, int x, int y, t_game *game);
int		handle_mouse_move(int x, int y, t_game *game);

// Player management
void	move_player(t_game *game, float cos_angle, float sin_angle, int tile_s);
void	rotate_player(t_player *player);
void	reset_player_var(t_player *player);
bool	corner_collision(t_game *game, int i, int j);

// RAYCASTING
void	render_walls(t_game *game);
void	init_ray(t_game *game, t_ray *ray, float ray_angle);
int		perform_dda(t_game *game, t_ray *ray);

// Raycasting utils
t_img	*get_texture(t_game *game, t_ray *ray);
void	calculate_wall_height(t_game *game, t_ray *ray);

// Drawing functions
void	draw_line(t_game *game, int x, t_point draw_s_e, int color);
void	draw_pixel(t_img *img, int x, int y, int color);

/* === PARSING ===*/
char	**get_map(const char *path);

/* = Configuration = */
int		init_config(t_game *game);

// Config utils
int		check_name_config(char *line);
char	*extract_path(char *line);
int		check_all_config_present(t_game *game);

// Validation config
int		is_valid_texture_path(const char *path);
int		is_valid_color(t_game *game, const char *color, int is_top);

// Load config
int		check_load_texture(t_game *game, char *line);

/* = Map = */
int		init_map(t_game *game);
char	**duplicate_map(char **map);
char	**normalize_map(char **map);

// Validate map
int		is_valid_map(char **map);
int		validate_horizontal(char **map);
int		has_single_player_start(char **map);
int		has_invalid_spaces(char **map);

/* === Utils === */
// error
int		print_error(char *msg, int ret);
void	*print_error_void(char *msg, void *ret);

// free
void	destroy_imgs(t_game *game);
void	free_map(char **map);
int		ft_free_tab_i(char **tab, int i);

// file utils
int		check_extension(const char *path, const char *ext);
int		open_file(const char *path);

// atoi safe
int		ft_atoi_safe(const char *str, int *valid);

// Split with sep
char	**ft_split_with_sep(const char *str, char sep);

// Map utils
int		is_line_empty(const char *line);
size_t	get_max_len(char **map);
size_t	get_map_height(char **map);
int		is_char_player(char c);

// Utils
int		get_pixel_color(t_img *img, int x, int y);
int		get_rgb_color(int r, int g, int b);

/* === Main === */
// Main utils
int		ft_exit(t_game *game);
int		init_base_img(t_game *game);

// Printing functions
void	print_map(char **map);
void	print_config(t_game *game);
void	print_player(t_player *player);
void	display_fps(t_fps *fps);

#endif
