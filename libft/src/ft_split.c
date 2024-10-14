/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:20:07 by ebayat            #+#    #+#             */
/*   Updated: 2024/07/14 11:14:58 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static char	**split(const char *str, char c, char **array, size_t word_count)
{
	size_t	start;
	size_t	end;
	size_t	i;

	i = 0;
	start = 0;
	while (i < word_count)
	{
		while (str[start] && str[start] == c)
			start++;
		end = start;
		while (str[end] && str[end] != c)
			end++;
		array[i] = ft_strndup(&str[start], end - start);
		if (!array[i])
		{
			ft_free_n_strs(i, &array);
			return (NULL);
		}
		i++;
		start = end;
	}
	array[i] = NULL;
	return (array);
}

char	**ft_split(const char *str, char delimiter)
{
	char	**array;
	size_t	word_count;

	word_count = ft_count_words(str, delimiter);
	array = ft_calloc((word_count + 1), sizeof(char *));
	if (!array)
		return (NULL);
	array = split(str, delimiter, array, word_count);
	return (array);
}
