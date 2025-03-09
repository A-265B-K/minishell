/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/05 18:34:38 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/03/09 11:16:14 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	clean_redir(t_commands *cmd, int sin, int sout, int serr)
{
	if (cmd->redirects.in_fd)
		dup2(sin, 0);
	if (cmd->redirects.out_fd)
		dup2(sout, 1);
	if (cmd->redirects.err_fd)
		dup2(serr, 2);
}

int	redirection_permission(t_commands *cmd)
{
	t_redirects	r;

	r = cmd->redirects;
	if ((r.sstdin != NULL && r.in_fd < 0) || \
	(r.sstdout != NULL && r.out_fd < 0) || (r.sstderr != NULL && r.err_fd < 0))
		return (0);
	else
		return (1);
}

static int	redirection_dup(t_shell *shell, t_commands *cmd)
{
	int	s_stdin;
	int	s_stdout;
	int	s_stderr;
	int	exitcode;

	s_stdin = 0;
	s_stdout = 0;
	s_stderr = 0;
	if (cmd->redirects.in_fd >= 0)
	{
		s_stdin = dup(0);
		close(0);
		dup2(cmd->redirects.in_fd, 0);
	}
	if (cmd->redirects.sstdout)
	{
		s_stdout = dup(1);
		close(1);
		dup2(cmd->redirects.out_fd, 1);
	}
	if (cmd->redirects.sstderr)
	{
		dup2(cmd->redirects.err_fd, STDOUT_FILENO);
		close(cmd->redirects.err_fd);
	}
	exitcode = execute_cmd(shell, cmd, 0);
	clean_redir(cmd, s_stdin, s_stdout, s_stderr);
	return (exitcode);
}

int	redirect_and_execute(t_shell *shell, t_commands *cmd, int pipe_fd)
{
	if (cmd->redirection)
		return (redirection_dup(shell, cmd));
	else
		return (execute_cmd(shell, cmd, pipe_fd));
}

void	handle_redirects(t_commands *cmd)
{
	char	*file;
	int		type;

	file = NULL;
	if (cmd->redirection)
	{
		if (cmd->redirection[1] == '>')
			type = 3;
		else if (cmd->redirection[0] == '>')
			type = 2;
		else
			type = 1;

		if (type == 3)
			file = ft_strlcpy2(cmd->redirection, 2);
		else
			file = ft_strlcpy2(cmd->redirection, 1);
		if (!file)
		{
			// handle proper exit
			return ;
		}
		else
		{
			if (type == 1)  // Input Redirection (<) // fix this part that it hangs
			{
				cmd->redirects.sstdin = file;
				cmd->redirects.in_fd = open(file, O_EXCL | O_RDONLY);
				if (cmd->redirects.in_fd == -1)
				{
					//	perror("open failed for input redirection");
					//	return;  // Handle error properly
				}
			}
			else
			{
				cmd->redirects.sstdin = NULL;
				cmd->redirects.in_fd = -1;
			}
			if (type == 2)
			{
				cmd->redirects.sstdout = file;
				cmd->redirects.out_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (cmd->redirects.out_fd == -1)
				{
				//	perror("open failed for output redirection");
				//	return;
				}
			}
			else
			{
				cmd->redirects.sstdout = NULL;
				cmd->redirects.out_fd = -1;
			}
			if (type == 3)
			{
				cmd->redirects.sstderr = file;
				cmd->redirects.err_fd = \
				open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (cmd->redirects.err_fd == -1)
				{
					//	perror("open failed for append redirection");
					return ;
				}
			}
			else
			{
				cmd->redirects.sstderr = NULL;
				cmd->redirects.err_fd = -1;
			}
		}
	}
}
