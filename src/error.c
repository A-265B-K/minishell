/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:43:38 by ahornstr          #+#    #+#             */
/*   Updated: 2025/03/28 02:01:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_handler(char *str, int exitcode)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (exitcode);
}

void	print_command_error(char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (errno == EISDIR)
		ft_putstr_fd("Is a directory\n", STDERR_FILENO);
	else if (errno == ENOENT && ft_strchr(cmd, '/'))
		ft_putstr_fd("No such file or directory\n", STDERR_FILENO);
	else if (errno == EACCES)
		ft_putstr_fd("Permission denied\n", STDERR_FILENO);
	else
		ft_putstr_fd("command not found\n", STDERR_FILENO);
}

void	path_error(t_commands *cmd)
{
	if (errno == EISDIR || (ft_strchr(cmd->str[0], '/') && errno == EACCES))
	{
		print_command_error(cmd->str[0]);
		exit(126);
	}
	print_command_error(cmd->str[0]);
	exit(127);
}
