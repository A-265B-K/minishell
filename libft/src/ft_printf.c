/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:56:03 by elie              #+#    #+#             */
/*   Updated: 2024/07/06 10:12:05 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	parse_conversion(char c, va_list args)
{
	if (c == 'c')
		return (ft_putchar_fd(va_arg(args, int), 1));
	if (c == 's')
		return (ft_putstr_fd(va_arg(args, char *), 1));
	if (c == 'p')
		return (ft_put_address(va_arg(args, void *)));
	if (c == 'd' || c == 'i')
		return (ft_putnbr_fd(va_arg(args, int), 1));
	if (c == 'u')
		return (ft_put_unum(va_arg(args, uint32_t)));
	if (c == 'x')
		return (ft_puthex(va_arg(args, uint32_t), "lower"));
	if (c == 'X')
		return (ft_puthex(va_arg(args, uint32_t), "upper"));
	if (c == '%')
		return (ft_putchar_fd('%', 1));
	return (0);
}

int	ft_printf(const char *printf_str, ...)
{
	va_list	args;
	size_t	character_counter;

	va_start(args, printf_str);
	character_counter = 0;
	while (*printf_str)
	{
		if (*printf_str == '%')
		{
			printf_str++;
			if (*printf_str == '\0')
				return (-1);
			character_counter += parse_conversion(*printf_str, args);
		}
		else
			character_counter += write(1, printf_str, 1);
		printf_str++;
	}
	va_end(args);
	return (character_counter);
}
