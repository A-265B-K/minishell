/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:44:01 by ebayat            #+#    #+#             */
/*   Updated: 2024/07/06 10:12:05 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*byte_dst;
	const char	*byte_src;

	byte_dst = (char *)dest;
	byte_src = (char *)src;
	if (!dest && !src)
		return (NULL);
	while (n--)
		*byte_dst++ = *byte_src++;
	return (dest);
}
