/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_with_sep.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 13:41:35 by rcaillie          #+#    #+#             */
/*   Updated: 2025/05/10 13:41:56 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_tokens(const char *str, char sep)
{
	int	i;
	int	count;
	int	in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (str[i])
	{
		if (str[i] == sep)
			count++;
		else if (!in_word)
		{
			count++;
			in_word = 1;
		}
		if (str[i] == sep)
			in_word = 0;
		i++;
	}
	return (count);
}

static char	*get_token(const char *str, char sep, int *index)
{
	int		start;
	char	*token;

	if (str[*index] == sep)
	{
		token = malloc(2);
		if (!token)
			return (NULL);
		token[0] = sep;
		token[1] = '\0';
		(*index)++;
		return (token);
	}
	start = *index;
	while (str[*index] && str[*index] != sep)
		(*index)++;
	token = ft_substr(str, start, *index - start);
	return (token);
}

char	**ft_split_with_sep(const char *str, char sep)
{
	char	**result;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	result = malloc(sizeof(char *) * (count_tokens(str, sep) + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		result[j] = get_token(str, sep, &i);
		if (!result[j])
			return (NULL);
		j++;
	}
	result[j] = NULL;
	return (result);
}
