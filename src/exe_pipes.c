/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 23:16:31 by marvin            #+#    #+#             */
/*   Updated: 2025/03/27 23:16:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe_ends(int prev_p, int *cur_p, t_commands *cmd)
{
	if (cur_p)
	{
		if (prev_p != -1)
			close(prev_p);
		if (cmd && cmd->next)
		{
			if (cur_p[1] != -1)
				close(cur_p[1]);
		}
		else if (cmd)
		{
			if (cur_p[0] != -1)
				close(cur_p[0]);
			if (cur_p[1] != -1)
				close(cur_p[1]);
		}
	}
}

int	wait_for_children(void)
{
	int		status;
	pid_t	pid;
	int		last_status;

	last_status = 0;
	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			last_status = 128 + WTERMSIG(status);
			if (WTERMSIG(status) == SIGPIPE)
				last_status = 0;
			if (WTERMSIG(status) == SIGINT)
				ft_putstr_fd("\n", STDERR_FILENO);
			else if (WTERMSIG(status) == SIGQUIT)
				signal(SIGQUIT, SIG_IGN);
		}
		pid = waitpid(-1, &status, 0);
	}
	if (pid == -1 && errno != ECHILD)
		return (error_handler("fork error", 1));
	return (last_status);
}

int	exe_pipe(t_shell *shell, t_commands *cmd, int *prev_p, int *cur_p)
{
	pid_t	pid;

	if (cmd->next && pipe(cur_p) == -1)
	{
		close_pipe_ends(*prev_p, cur_p, cmd);
		return (error_handler("pipe error", 1));
	}
	pid = fork();
	if (pid == -1)
	{
		close_pipe_ends(*prev_p, cur_p, cmd);
		return (error_handler("fork error", 1));
	}
	if (pid == 0)
	{
		set_child_redir(*prev_p, cur_p, cmd);
		if (cmd->builtin)
			exit(execute_builtin(shell, cmd));
		execute_external(cmd, shell);
	}
	close_pipe_ends(*prev_p, cur_p, cmd);
	*prev_p = cur_p[0];
	return (0);
}

int	execute_pipes(t_shell *shell)
{
	int			prev_pipe_in;
	int			current_pipe[2];
	t_commands	*cmd;

	prev_pipe_in = -1;
	cmd = shell->com_struct;
	while (cmd)
	{
		current_pipe[0] = -1;
		current_pipe[1] = -1;
		if (exe_pipe(shell, cmd, &prev_pipe_in, current_pipe))
			return (1);
		cmd = cmd->next;
	}
	shell->exitcode = wait_for_children();
	return (shell->exitcode);
}
