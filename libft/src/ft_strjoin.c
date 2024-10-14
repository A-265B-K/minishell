/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:16:19 by ebayat            #+#    #+#             */
/*   Updated: 2024/07/06 10:12:05 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	char	*new_str_pointer;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	new_str = ft_calloc(len, sizeof(char));
	if (!new_str)
		return (NULL);
	new_str_pointer = new_str;
	while (*s1)
		*new_str++ = *s1++;
	while (*s2)
		*new_str++ = *s2++;
	return (new_str_pointer);
}
