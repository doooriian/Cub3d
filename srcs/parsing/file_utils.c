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

int	check_extension(const char *path)
{
	size_t	len;

	len = ft_strlen(path);
	return (len > 4 && !ft_strncmp(path + len - 4, ".cub", 4));
}

int	open_file(const char *path)
{
	if (access(path, F_OK) < 0 || access(path, R_OK) < 0)
		return (-1);
	return (open(path, O_RDONLY));
}
