# include <minishell.h>
#include <errno.h>
// make it so the last command is executed in the parent


int	ft_strcmp2(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (unsigned char)(*s1) - (unsigned char)(*s2);
}

void	execute_builtin(t_shell *shell, t_commands *cmd)
{
	if(!ft_strcmp2(cmd->builtin, "pwd"))
			shell->exitcode = ft_pwd();
	else if(!ft_strcmp2(cmd->builtin, "echo"))
			shell->exitcode =ft_echo(cmd->str, shell);
	else if(!ft_strcmp2(cmd->builtin, "cd"))
			shell->exitcode = ft_cd(cmd->str);
	else if(!ft_strcmp2(cmd->builtin, "export"))
			shell->exitcode = ft_export(cmd->str);
	else if(!ft_strcmp2(cmd->builtin, "unset"))
			shell->exitcode = ft_unsetenv(cmd->str);
	else if(!ft_strcmp2(cmd->builtin, "env"))
			shell->exitcode = ft_env();
	else if(!ft_strcmp2(cmd->builtin, "exit"))
			ft_exit(cmd->str, shell->exitcode);
//	dprintf(2, "Exitcode in struct: %d\n", shell->exitcode);
}

int	execute_cmd(t_shell *shell, t_commands *cmd)
{
	if (cmd->builtin)
	{
		execute_builtin(shell, cmd);
		exit(0);
	}
	char *file_path;
	if (cmd->str[0][0] == '/' || cmd->str[0][0] == '.')
	{
		if (cmd->str[0][0] == '/')
		{
			file_path = ft_strjoin("/", cmd->str[0] + 1);
		}
		if (cmd->str[0][0] == '.')
		{
			char buf[100];
			file_path = ft_strjoin(getcwd(buf, 100), cmd->str[0] + 2);
		}
		if (access(file_path, F_OK))
		{
			dprintf(2, " No such file or directory\n");
			return (127);
		}
		return(0);
	}

// int is_regular_file(const char *path)
// {
//     struct stat path_stat;
//     stat(path, &path_stat);
//     return S_ISREG(path_stat.st_mode);
// }


	char	*function_name = ft_strjoin("/usr/bin/", cmd->str[0]);
	if (execve(function_name, cmd->str + 1, (char *const *)borrow_env()) == -1)
	{
		dprintf(2, " command not found\n");
		return (127);
	}
	return (0);
}

int	redirect_and_execute(t_shell *shell, t_commands *cmd, char *str)
{
	int	i = 1;
	int	out_fd;
	//int	pipe_fd[2];
	pid_t pid;

	//pipe(pipe_fd);

	if (cmd->builtin && !cmd->next)
	{
		execute_builtin(shell, cmd);
		return (0);
	}
	if (!cmd->next)
	{
		shell->exitcode = execute_cmd(shell, cmd);
		return (0);
	}
	if (str)
	{
		// google clobber	
		if (str[i] == '>')
		{
			i += 1;
			out_fd = open(str + i, O_CREAT | O_WRONLY | O_APPEND, 0644);
		}
		else
			out_fd = open(str + i, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (out_fd < 0)
		{
			perror("Open");
			return (1);
		}
	}
	else
		out_fd = open("/dev/stdout", O_WRONLY);
	pid = fork();
	if (!pid)
	{
		dup2(out_fd, STDOUT_FILENO);
		execute_cmd(shell, cmd);
		exit(0);
	}
	else
	{
		waitpid(0, NULL, 0);
		close(out_fd);
	}
	return (0);
}

int	execute(t_shell *shell)
{
	t_commands *cmd;
	cmd = shell->com_struct;
	redirect_and_execute(shell, cmd, cmd->redirection);
	while(cmd->next)
	{
		cmd = cmd->next;
		redirect_and_execute(shell, cmd, cmd->redirection);
	}
	return (0);
}
