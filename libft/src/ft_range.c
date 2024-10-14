/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 17:19:41 by elie              #+#    #+#             */
/*   Updated: 2024/07/06 10:12:05 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	*ft_range(int start, int end)
{
	int	difference;
	int	*array;
	int	increment;
	int	i;

	if (start > end)
	{
		difference = start - end;
		increment = -1;
	}
	else
	{
		difference = end - start;
		increment = 1;
	}
	array = ft_calloc((difference), sizeof(int));
	if (!array)
		return (NULL);
	i = 0;
	while (i < difference)
	{
		array[i] = start + (i * increment);
		i++;
	}
	return (array);
}
