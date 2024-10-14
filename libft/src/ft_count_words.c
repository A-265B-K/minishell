/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:33:12 by elie              #+#    #+#             */
/*   Updated: 2024/07/06 10:12:05 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	ft_count_words(const char *str, char delimiter)
{
	size_t	count;
	size_t	i;
	int		inside_word;

	count = 0;
	i = 0;
	inside_word = 0;
	while (str[i])
	{
		if (str[i] == delimiter)
		{
			if (inside_word)
			{
				count++;
				inside_word = 0;
			}
		}
		else
			inside_word = 1;
		i++;
	}
	if (inside_word)
		count++;
	return (count);
}
