/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_redirects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 22:53:43 by marvin            #+#    #+#             */
/*   Updated: 2025/03/27 22:53:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_pipe_redir(int prev_in, int *curr_pipe, t_commands *cmd)
{
	if (prev_in != -1)
	{
		dup2(prev_in, STDIN_FILENO);
		close(prev_in);
	}
	if (cmd->next && curr_pipe[1] != -1)
	{
		dup2(curr_pipe[1], STDOUT_FILENO);
		close(curr_pipe[1]);
	}
	if (curr_pipe[0] != -1)
		close(curr_pipe[0]);
}

void	redirect(char *redir, int is_last_command)
{
	int	fd;
	int	std_fd;

	if (redir[0] == '>')
	{
		if (redir[1] == '>')
			fd = open(redir + 2, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(redir + 1, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		std_fd = STDOUT_FILENO;
	}
	else
	{
		fd = open(redir + 1, O_RDONLY);
		std_fd = STDIN_FILENO;
	}
	if (fd == -1 || dup2(fd, std_fd) == -1)
	{
		perror("minishell");
		if (!is_last_command)
			exit(0);
		exit(1);
	}
	close(fd);
}

void	set_child_redir(int prev_p_in, int *cur_p, t_commands *cmd)
{
	int	i;
	int	is_last_command;

	set_pipe_redir(prev_p_in, cur_p, cmd);
	if (!cmd->redirection)
		return ;
	i = 0;
	is_last_command = (cmd->next == NULL);
	while (cmd->redirection[i])
	{
		redirect(cmd->redirection[i], is_last_command);
		i++;
	}
}
