/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 08:10:53 by elie              #+#    #+#             */
/*   Updated: 2024/07/06 10:12:05 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_alloc(char *str)
{
	int		i;
	int		len;
	char	*return_str;

	i = 0;
	len = ft_strlen(str);
	return_str = ft_calloc((len + 1), sizeof(char));
	if (!return_str)
		return (NULL);
	while (i < len)
	{
		return_str[i] = str[i];
		i++;
	}
	return (return_str);
}
