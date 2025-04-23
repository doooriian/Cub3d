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

float	conver_to_radian(int degree)
{
	return (degree * (M_PI / 180));
}

float	conver_to_degree(float radian)
{
	return (radian * (180 / M_PI));
}

int	main(void)
{
	printf("Hello, World!\n");
	printf("PI: %f\n", M_PI);
	printf("90 degrees in radians: %f\n", conver_to_radian(90));
	printf("PI in degrees: %f\n", conver_to_degree(M_PI));
	return (0);
}
