/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:01:04 by marvin            #+#    #+#             */
/*   Updated: 2025/03/23 14:01:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_child(t_shell *shell, t_commands *cmd, \
							int fd[2], int *pipe_fd)
{
	if (*pipe_fd != 0)
	{
		dup2(*pipe_fd, 0);
		close(*pipe_fd);
	}
	if (cmd->next)
	{
		dup2(fd[1], 1);
	}
	if (fd[0] >= 0)
		close(fd[0]);
	if (fd[1] >= 0)
		close(fd[1]);
	exit(redirect_and_execute(shell, cmd, *pipe_fd));
}

int	run_pipe(t_shell *shell, t_commands *cmd, int pipe_fd, int *child_exitcode)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) && cmd->next)
		return (-1);
	// printf("fd == [%d][%d]\n", fd[0], fd[1]);
	pid = fork();
	if (pid < 0)
	{
		if (fd[0] >= 0)
			close(fd[0]);
		if (fd[1] >= 0)
			close(fd[1]);
		if (pipe_fd != 0)
			close(pipe_fd);
		close(pipe_fd);
		return (-1);
	}
	else if (!pid)
		execute_child(shell, cmd, fd, &pipe_fd);
	waitpid(pid, child_exitcode, 0);
	shell->exitcode = WEXITSTATUS(*child_exitcode);
	if (pipe_fd != 0)
		close(pipe_fd);
	close(fd[1]);
	return (fd[0]);
}

void	execute_pipe(t_shell *shell, t_commands *cmd)
{
	int	pipe_fd;
	int	child_exitcode;

	pipe_fd = -1;
	while (cmd)
	{
		pipe_fd = run_pipe(shell, cmd, pipe_fd, &child_exitcode);
		cmd = cmd->next;
		if (cmd)
			handle_redirects(cmd);
	}
}