/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:37:34 by ebayat            #+#    #+#             */
/*   Updated: 2024/07/06 10:12:05 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				len;
	unsigned char	chr;

	chr = (unsigned char)c;
	len = ft_strlen(s);
	if (chr == '\0')
		return ((char *)s + len);
	while (len >= 0)
	{
		if (s[len] == chr)
			return ((char *)&s[len]);
		len--;
	}
	return (NULL);
}
