/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 21:01:25 by marvin            #+#    #+#             */
/*   Updated: 2025/03/27 21:01:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isstrnum(char *str)
{
	int	flag;

	flag = 1;
	if (!str || *str == '\0')
		return (0);
	if (*str == '+' || *str == '-')
		str += 1;
	while (*str)
	{
		if (!ft_isdigit(*str))
		{
			flag = 0;
			break ;
		}
		str += 1;
	}
	return (flag);
}

void	ft_exit(char **params, int exitcode)
{
	if (!params)
		exit(exitcode);
	if (!params[0])
		exit(exitcode);
	if (params[1])
	{
		ft_putstr_fd(" too many arguments\n", 2);
		exit(1);
	}
	if (!ft_isstrnum(params[0]))
	{
		ft_putstr_fd(" numeric argument required\n", 2);
		exit(2);
	}
	exitcode = ft_atoi(params[0]);
	exit(exitcode);
}
