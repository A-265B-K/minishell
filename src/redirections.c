# include <minishell.h>

static void redirection_dup(t_shell *shell, t_commands *cmd)
{
	// int	s_stdin;
	// int	s_stdout;
	// int	s_stderr;

	(void)shell;
	printf("%s\n", cmd->redirection);

	// if (!(s_stdin = 0) && cmdarg->redir.in != NULL)
	// {
	// 	s_stdin = dup(0);
	// 	close(0);
	// 	dup2(cmdarg->redir.sstdin, 0);
	// }
	// if (!(s_stdout = 0) && cmdarg->redir.out1)
	// {
	// 	s_stdout = dup(1);
	// 	close(1);
	// 	dup2(cmdarg->redir.sstdout, 1);
	// }
	// if (!(s_stderr = 0) && cmdarg->redir.out2)
	// {
	// 	s_stderr = dup(2);
	// 	close(2);
	// 	dup2(cmdarg->redir.sstderr, 2);
	// }
	// exec(cmdarg->args, 0, cmdarg);
	// clean_redir(cmdarg, s_stdin, s_stdout, s_stderr);
}