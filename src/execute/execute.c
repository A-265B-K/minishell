
#include "../../include/minishell.h"

static void	execute_fork(t_pipe *pipe, t_shell *shell)
{
	char	*executable;

	pipe->pid = fork();
	signal(SIGINT, signal_handler_forked);
	if (pipe->pid == 0)
	{
		debug("forked");
		if (!builtins(pipe->argc, pipe->argv, shell->envp, shell))
		{
			executable = where(pipe->argv[0], shell);
			// redir_task(shell, pipe);
			execve(executable, pipe->argv, shell->envp);
			if (errno == 13)
			{
				printf("minishell: permission denied: %s\n", pipe->argv[0]);
				exit (126);
			}
			else
			{
				printf("minishell: %s: %s\n", pipe->argv[0], strerror(errno));
				printf("minishell: command not found: %s\n", pipe->argv[0]);
				exit (127);
			}
		}
		exit (0);
	}
}

static void	execute_last(t_pipe *pipe, t_shell *shell)
{
	if (!builtins(pipe->argc, pipe->argv, shell->envp, shell))
	{
		printf(GREEN"last executed\n"WHITE);
		execute_fork(pipe, shell);
	}
	if (ft_strncmp(pipe->argv[0], "exit", ft_strlen(pipe->argv[0])) == 0)
		shell->exit = true;
}

void	wait_for_processes(t_list *pipes, t_shell *shell)
{
	t_pipe	*pipe;

	while (pipes)
	{
		pipe = pipes->content;
		if (pipe->pid != 0)
		{
			debug("waiting for process");
			wait4(pipe->pid, &pipe->wstatus, 0, NULL);
			if (WIFEXITED(pipe->wstatus))
				shell->exitcode = WEXITSTATUS(pipe->wstatus);
			if (WIFSIGNALED(pipe->wstatus))
				shell->exitcode = WTERMSIG(pipe->wstatus) + 128;
			debug("process done");
		}
		pipes = pipes->next;
	}
}

static bool	invalid_pipe(t_pipe *pipe)
{
	if (pipe->argc == 0)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (true);
	}
	if (pipe->invalid != -1)
	{
		printf("minishell: syntax error near unexpected token %s\n",
			pipe->argv[pipe->invalid]);
		return (true);
	}
	return (false);
}
// void	redir_task(t_shell *shell, t_pipe *pipe)
// {
// 	t_task	*task;
// 	t_list	*tasks;
	
// 	tasks = shell->tasks;
// 	while (tasks && tasks->content)
// 	{
// 		task = tasks->content;
		

// 		tasks = tasks->next;
// 	}
		
	
// 	// find operator
// 	// change pipe_fd to in and out of next
// 	if ()
// 	if ()
	
// }

t_state	execute(t_shell *shell)
{
	t_list	*tasks;
	t_list	*pipes;

	tasks = shell->tasks;
	while (tasks && tasks->content)
	{
		pipes = ((t_task *)tasks->content)->pipes;
		while (pipes)
		{
			
			expander(pipes->content, shell);
			if (invalid_pipe(pipes->content))
				return (CONTINUE);
			if (pipes->next)
			{
				printf(GREEN"executing fork\n"WHITE);
				execute_fork(pipes->content, shell);
			}
			else
				execute_last(pipes->content, shell);
			if (shell->exit == true)
				return (EXIT);
			print_pipe(pipes->content);
			pipes = pipes->next;
		}
		wait_for_processes(((t_task *)tasks->content)->pipes, shell);
		tasks = tasks->next;
	}
	return (CONTINUE);
}
void	print_pipe(t_pipe *pipes)
{
	printf(BLUE"INDEX = %d\n"WHITE, pipes->index);
	printf(BLUE"invalid = %d\n"WHITE, pipes->invalid);
	printf(BLUE"pid = %d\n"WHITE, pipes->pid);
	printf(BLUE"wstatus = %d\n"WHITE, pipes->wstatus);
	int	i = 0;
	// if (pipes->envp)
	// {
	// 	while (pipes->envp[i])
	// 	{
		
	// 		printf(BLUE"envp[%d] = %s\n"WHITE, i, pipes->envp[i]);
	// 		i++;	
	// 	}
	// }
	i = 0;
	if (pipes->argv)
	{
		while (pipes->argv[i])
		{
			printf(BLUE"argv[%d] = %s\n"WHITE, i, pipes->argv[i]);
			i++;
		}
	}
	printf(BLUE"argc = %d\n"WHITE, pipes->argc);
	printf(BLUE"is_exit = %d\n"WHITE, pipes->is_exit);
}
