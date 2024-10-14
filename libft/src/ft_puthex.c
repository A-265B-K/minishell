/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 11:23:37 by elie              #+#    #+#             */
/*   Updated: 2024/02/11 11:54:42 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_puthex(uint64_t num, const char *upper_or_lower)
{
	size_t		i;
	char		*num_as_hex;
	int			printed;
	const char	*set;

	set = "0123456789abcdef";
	if (num == 0)
		return (ft_putchar_fd('0', 1));
	if (ft_strncmp(upper_or_lower, "upper", 5) == 0)
		set = "0123456789ABCDEF";
	i = ft_hex_len(num);
	num_as_hex = ft_calloc((i-- + 1), sizeof(char));
	if (!num_as_hex)
		return (0);
	printed = 0;
	while (num)
	{
		num_as_hex[i--] = set[num % 16];
		num /= 16;
		printed++;
	}
	ft_putstr_fd(num_as_hex, 1);
	free(num_as_hex);
	return (printed);
}
