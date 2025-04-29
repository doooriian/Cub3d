/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:51:17 by rcaillie          #+#    #+#             */
/*   Updated: 2025/04/29 13:51:17 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*sanitize_line(const char *line)
{
	size_t	i;
	size_t	j;
	char	*out;

	i = 0;
	j = 0;
	out = malloc(ft_strlen(line) + 1);
	if (!out)
		return (NULL);
	while (line[i])
	{
		if (line[i] != '\n')
		{
			out[j] = line[i];
			j++;
		}
		i++;
	}
	out[j] = '\0';
	return (out);
}

static int	count_lines(const char *path)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open_file(path);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		count++;
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

static int	fill_map(char **map, const char *path)
{
	int		fd;
	int		i;
	char	*line;

	fd = open_file(path);
	if (fd < 0)
		return (-1);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		map[i] = sanitize_line(line);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

char	**get_map(const char *path)
{
	char	**map;
	int		lines;

	lines = count_lines(path);
	if (lines < 0)
		return (NULL);
	map = ft_calloc(lines + 1, sizeof(char *));
	if (!map)
		return (NULL);
	if (fill_map(map, path) < 0)
	{
		free_map(map);
		return (NULL);
	}
	return (map);
}
