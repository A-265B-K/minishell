/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:42:35 by ebayat            #+#    #+#             */
/*   Updated: 2024/07/06 10:12:05 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

static uint32_t	get_digits(int n)
{
	size_t	digits;

	digits = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		digits++;
	}
	while (n != 0)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

static void	convert(char *str, long int n, int digits, int negative)
{
	while (digits--)
	{
		str[digits] = '0' + (n % 10);
		n /= 10;
	}
	if (negative)
		str[0] = '-';
}

char	*ft_itoa(int n)
{
	int			digits;
	char		*str;
	int			negative;
	long int	num;

	num = n;
	negative = 0;
	digits = get_digits(n);
	str = ft_calloc((digits + 1), sizeof(char));
	if (!str)
		return (NULL);
	if (num < 0)
	{
		negative = 1;
		num = -num;
	}
	convert(str, num, digits, negative);
	return (str);
}
