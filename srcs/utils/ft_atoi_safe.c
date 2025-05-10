/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_safe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:04:12 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/10 14:23:22 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	skip_whitespace_and_sign(const char *str, int *sign)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*sign = -1;
		i++;
	}
	return (i);
}

static int	handle_overflow(long long res, int sign, int *valid)
{
	if ((sign == 1 && res > 2147483647) || (sign == -1 && - res < -2147483648))
	{
		*valid = 0;
		return (1);
	}
	return (0);
}

static int	convert_to_int(const char *str, int *valid, int i, int sign)
{
	long long	res;
	int			has_digit;

	res = 0;
	has_digit = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		has_digit = 1;
		res = res * 10 + (str[i] - '0');
		if (handle_overflow(res, sign, valid))
			return (0);
		i++;
	}
	if (!has_digit || str[i] != '\0')
		*valid = 0;
	return ((int)(res * sign));
}

/**
 * Converts a string to an integer safely.
 * If the conversion is invalid, sets the valid flag to 0.
 * Otherwise, sets it to 1.
 * @brief Converts a string to an integer safely.
 * @param str The string to convert.
 * @param valid Pointer to an integer that will be set to 1
 * if the conversion is valid.
 */
int	ft_atoi_safe(const char *str, int *valid)
{
	int	sign;
	int	i;

	*valid = 1;
	sign = 1;
	i = skip_whitespace_and_sign(str, &sign);
	return (convert_to_int(str, valid, i, sign));
}
