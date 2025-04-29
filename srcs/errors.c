/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 09:49:20 by rcaillie          #+#    #+#             */
/*   Updated: 2025/04/29 09:49:20 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	print_error(char *msg, int ret)
{
	if (msg)
		ft_putendl_fd(msg, 2);
	else
		ft_putendl_fd("Error", 2);
	return (ret);
}
