/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:56:04 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/10 23:11:52 by rcaillie         ###   ########.fr       */
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

// Constants
# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define WIDTH		1000
# define HEIGHT		800
# define MAP_WIDTH	800
# define MAP_HEIGHT	600
# define SPEED		0.5
# define ANGLE_SPEED	0.03
# define RAYS		1
# define PI 			3.14159265
# define TEX_WIDTH 	64
# define TEX_HEIGHT 	64

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
}	t_img;

typedef struct s_imgs
{
	t_img	no;
	t_img	ea;
	t_img	so;
	t_img	we;
	t_img	base;
	t_img	map;
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
	int		side; // 0 si c'est un mur vertical, 1 si c'est un mur horizontal
}	t_ray;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*win_map;
	int			tile_size;
	int			map_offset_x;
	int			map_offset_y;
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

void	draw_compass(t_game *game);
void	draw_triangle(t_game *game, t_point p1, t_point p2, t_point p3, int color);
void	draw_center_circle(t_game *game, int cx, int cy, int radius, int color);
t_point	get_point(float angle, int length, int cx, int cy);
void	draw_line2(t_game *game, t_point p0, t_point p1, int color);

// General
int		ft_exit(t_game *game);
int		get_rgb_color(int r, int g, int b);

void	render_walls(t_game *game);

// Initialization
void	init_data(t_game *game);
void	init_player(t_player *player, t_game *game);
int		init_base_img(t_game *game);


// Player management
void	reset_player_var(t_player *player);
void	rotate_player(t_player *player);
void	move_player(t_game *game, float cos_angle,
			float sin_angle, int tile_size);

// Key hooks
int		loop(t_game *game);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_player *player);

// MINIMAP
int		minimap_init(t_game *game);
void	draw_square(t_img *img, t_point point, int size, int color);
void	render_minimap(t_game *game);
int		update_minimap_loop(t_game *game);
void	draw_ray_line(t_game *game, t_player *player, float angle);
void	render_rays_on_minimap(t_game *game, t_player *player);
bool	is_ray_touching_wall(t_game *game, float ray_x, float ray_y);

// File utilities
int		check_extension(const char *path, const char *ext);
int		open_file(const char *path);

int	is_char_player(char c);

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
void	*print_error_void(char *msg, void *ret);

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
void	print_player(t_player *player);
void	display_fps(t_fps *fps);

// Map validation
char	**ft_split_with_sep(const char *str, char sep);
int		ft_atoi_safe(const char *str, int *valid);
int		validate_horizontal(char **map);

// Raycasting
void	init_ray(t_game *game, t_ray *ray, float ray_angle);
void	advance_ray(t_ray *ray);
void	calculate_perpendicular_distance(t_game *game, t_ray *ray);
int		perform_dda(t_game *game, t_ray *ray);

// Wall rendering
void	calculate_wall_height(t_game *game, t_ray *ray);
void	draw_pixel(t_img *img, int x, int y, int color);
void	draw_line(t_game *game, int x, int draw_start, int draw_end, int color);
t_img	*get_texture(t_game *game, t_ray *ray);
void	draw_wall_tx(t_game *game, t_ray *ray, int x);
void	draw_wall_color(t_game *game, t_ray *ray, int x);
void	draw_all(t_game *game, t_ray *ray, int x);
void	render_walls(t_game *game);
void	draw_ceiling_and_floor(t_game *game, int x);

#endif
