/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahornstr <ahornstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:43:38 by ahornstr          #+#    #+#             */
/*   Updated: 2024/11/20 16:43:56 by ahornstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error(char *str)
{
	if (errno != 0)
	{
		if (str)
			perror(str);
		else
			perror("Error");
		return (errno);
	}
	if (str)
	{
		ft_putstr_fd("Error: ", STDERR_FILENO);
		ft_putendl_fd(str, STDERR_FILENO);
	}
	else
		ft_putendl_fd(ERR_UNKOWN, STDERR_FILENO);
	return (EXIT_FAILURE);
}