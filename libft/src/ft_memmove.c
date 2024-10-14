/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:05:45 by ebayat            #+#    #+#             */
/*   Updated: 2024/07/06 10:12:05 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*byte_dst;
	const unsigned char	*byte_src;

	if (!dest && !src)
		return (NULL);
	byte_src = (const unsigned char *)src;
	byte_dst = (unsigned char *)dest;
	if (byte_dst < byte_src)
	{
		while (n--)
			*byte_dst++ = *byte_src++;
	}
	else
	{
		byte_dst += n;
		byte_src += n;
		while (n--)
			*(--byte_dst) = *(--byte_src);
	}
	return (dest);
}
