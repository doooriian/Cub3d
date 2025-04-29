/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:54:37 by rcaillie          #+#    #+#             */
/*   Updated: 2025/04/29 10:54:37 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char *sanitize_line(const char *line)
{
	size_t i, j;
	char *out;

	out = malloc(ft_strlen(line) + 1);
	if (!out)
		return (NULL);
	i = 0; j = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			out[j++] = line[i];
		i++;
	}
	out[j] = '\0';
	return (out);
}

char **read_map(const char *path)
{
	int   fd;
	char *line;
	char **map = NULL;
	size_t count = 0;

	fd = open_file(path);
	if (fd < 0)
		return (NULL);

	// First pass: count lines
	while ((line = get_next_line(fd)))
	{
		free(line);
		count++;
	}
	close(fd);

	// Allocate
	map = ft_calloc(count + 1, sizeof(char *));
	if (!map)
		return (NULL);

	// Second pass: read and sanitize
	fd = open_file(path);
	count = 0;
	while ((line = get_next_line(fd)))
	{
		map[count++] = sanitize_line(line);
		free(line);
	}
	map[count] = NULL;
	close(fd);
	return (map);
}

void free_map(t_map map)
{
	for (size_t i = 0; map[i]; i++)
		free(map[i]);
	free(map);
}