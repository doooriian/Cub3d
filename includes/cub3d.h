/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:56:04 by rcaillie          #+#    #+#             */
/*   Updated: 2025/04/23 15:56:04 by rcaillie         ###   ########.fr       */
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

// -- Constants -- //
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720


// -- Structs -- //
typedef char **t_map;

// -- Functions -- //

// Parsing -- //
int check_extension(const char *path);
int open_file(const char *path);
char **read_map(const char *path);
char *sanitize_line(const char *line);
void free_map(t_map map);
int validate_map(t_map map);

int	print_error(char *msg, int ret);


#endif