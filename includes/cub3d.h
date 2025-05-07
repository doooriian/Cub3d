/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:56:04 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/07 18:50:00 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "libft.h"
# include "get_next_line.h"
# include <MLX42/MLX42.h>


# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

typedef struct s_map_info
{
	int		index;
	char	**map;
	int		floor_color[3];
	int		top_color[3];
	int		top_color_set;
	int		floor_color_set;
}	t_map_info;

typedef struct s_pos
{
	int		x;
	int		y;
	char	c;
}	t_pos;

typedef struct s_player
{
	t_pos	pos;
	int		dir; // 0: N, 1: E, 2: S, 3: W
}	t_player;

typedef struct s_tx
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
}	t_tx;

typedef struct s_img
{
	mlx_image_t	*no;
	mlx_image_t	*so;
	mlx_image_t	*we;
	mlx_image_t	*ea;
}	t_img;

typedef struct s_game
{
	void		*mlx;
	t_map_info	map_info;
	t_player	player;
	t_tx		tx;
	t_img		img;
}	t_game;

// File utilities
int		check_extension(const char *path, const char *ext);
int		open_file(const char *path);

// Map utilities
char	**get_map(const char *path);
void	free_map(char **map);
int		is_valid_map(char **map);

// Error handling
int		print_error(char *msg, int ret);

// Configuration parsing
int		init_config(t_game *game);
int		check_name_config(char *line);
int		start_with(char *line, const char *prefix);
char	*extract_path(char *line);
int		check_all_config_present(t_game *game);
int		check_load_texture(t_game *game, char *line);
int		load_config(t_game *game, int type, char *path);

// Resource management
void	free_img(t_game *game);
void	free_tx(t_game *game);

#endif