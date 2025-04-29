/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:52:52 by rcaillie          #+#    #+#             */
/*   Updated: 2025/04/29 10:52:52 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * * @brief Check if the file has the specified extension
 * *
 * * @param path The file path to check
 * * @param ext The expected file extension (e.g., ".cub")
 * * @return 1 if the file has the expected extension, 0 otherwise
 */
int	check_extension(const char *path, const char *ext)
{
	size_t	len;

	len = ft_strlen(path);
	return (len > 4 && !ft_strncmp(path + len - ft_strlen(ext),
			ext, ft_strlen(ext)));
}

int	open_file(const char *path)
{
	if (access(path, F_OK) < 0 || access(path, R_OK) < 0)
		return (-1);
	return (open(path, O_RDONLY));
}
