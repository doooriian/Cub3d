/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:55:43 by rcaillie          #+#    #+#             */
/*   Updated: 2025/04/23 15:55:43 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
	t_map map;

	if (argc != 2)
		return (print_error("Error: Invalid number of arguments", 1));

	if (!check_extension(argv[1]))
		return (print_error("Error: Expected .cub extension", 1));

	map = read_map(argv[1]);
	if (!map)
		return (print_error("Error: Failed to read map", 1));

	if (validate_map(map) < 0)
	{
		free_map(map);
		return (1);
	}

	// Continue with game initialization...
	free_map(map);
	printf("Map loaded successfully\n");
	return (0);
}
