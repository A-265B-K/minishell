/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_address.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 11:24:57 by elie              #+#    #+#             */
/*   Updated: 2024/02/11 11:46:29 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_put_address(void *ptr)
{
	uint64_t	address;

	address = (uint64_t)ptr;
	if (ptr)
	{
		ft_putstr_fd("0x", 1);
		return (2 + ft_puthex(address, "lower"));
	}
	return (ft_putstr_fd("(nil)", 1));
}
