/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/09 16:30:42 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/02/24 16:07:24 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_strcmp2(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (s1 ? 1 : (s2 ? -1 : 0));
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return ((unsigned char)(*s1) - (unsigned char)(*s2));
		s1++;
		s2++;
	}
	return ((unsigned char)(*s1) - (unsigned char)(*s2));
}


char *ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
    char *res;
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    size_t len3 = strlen(s3);

    res = malloc(len1 + len2 + len3 + 1);
    if (!res)
        return (NULL);
    strcpy(res, s1);
    strcat(res, s2);
    strcat(res, s3);
    return (res);
}


int	execute_builtin(t_shell *shell, t_commands *cmd, int pipe_fd)
{
	(void)pipe_fd;
	if (!ft_strcmp2(cmd->builtin, "pwd"))
		shell->exitcode = ft_pwd();
	else if (!ft_strcmp2(cmd->builtin, "echo"))
		shell->exitcode = ft_echo(cmd->str);
	else if (!ft_strcmp2(cmd->builtin, "cd"))
		shell->exitcode = ft_cd(cmd->str);
	else if (!ft_strcmp2(cmd->builtin, "export"))
		shell->exitcode = ft_export(cmd->str);
	else if (!ft_strcmp2(cmd->builtin, "unset"))
		shell->exitcode = ft_unsetenv(cmd->str);
	else if (!ft_strcmp2(cmd->builtin, "env"))
		shell->exitcode = ft_env();
	else if (!ft_strcmp2(cmd->builtin, "exit"))
		ft_exit(cmd->str, shell->exitcode);
	else
		return (0);
	return (1);
}

int	is_dir(const char *file_path)
{
	struct stat	path_stat;

	if (!stat(file_path, &path_stat))
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

void	debug_fds(const char *msg)
{
	printf("%s\n", msg);
	for (int fd = 0; fd < 10; fd++)
	{
		if (fcntl(fd, F_GETFD) != -1)
			dprintf(2, "FD %d is open\n", fd);
	}
}

int	execute_string(t_shell *shell, t_commands *cmd, char *str, int pipe_fd)
{
	pid_t	pid;

	(void)shell;
	if (!pipe_fd)
		pid = fork();
	if (!pipe_fd && pid < 0)
	{
		free(str);
		dprintf(2, "execve: failed to fork\n");
		return (-1);
	}
	else if(!pid)
		execve(str, cmd->str, (char *const *)borrow_env());
	free(str);
	if (pipe_fd)
		return (1);
	if (ft_strcmp2(cmd->str[0], "./minishell"))
		signal(SIGINT, SIG_IGN);
	wait(&pid);
	//status_child();
	pid = 0;
	return (1);
}

int		check_perms(t_shell *shell, t_commands *cmd, char *bin, struct stat statbuf, int pipe_fd)
{
	if (statbuf.st_mode & S_IFREG)
	{
		if (statbuf.st_mode & S_IXUSR)
			return (execute_string(shell, cmd, bin, pipe_fd));
		else
		{
			dprintf(2, "minishell: execve: permission denied: %s\n", bin);
		//	g_status = 1;
		}
		free(bin);
		return (1);
	}
	else
	{
		dprintf(2, "minishell: %s : Is a directory\n", cmd->str[1]);
	//	g_status = 1;
	}
	free(bin);
	return (1);
}

int	execute_binaries(t_shell *shell, t_commands *cmd, int	pipe_fd)
{
	struct stat	statbuf;
	char		*path_env;
	char		*path;
	char		*bin;
	char		*saveptr;

	// MAKE STRTOK_R

	path_env = ft_getenv("PATH");
	if (!path_env || !*path_env)
		return (-1);
	path = strtok_r(path_env, ":", &saveptr);
	while (path)
	{
		bin = ft_strjoin3(path, "/", cmd->str[0]);
		if (!lstat(bin, &statbuf))
		{
			free(path_env);
			return (check_perms(shell, cmd, bin, statbuf, pipe_fd));
		}
		free(bin);
		path = strtok_r(NULL, ":", &saveptr);  // Get next path
	}
	free(path_env);
	return (0);
}

static int	execute_files(t_shell *shell, t_commands *cmd, int pipe_fd)
{
	struct stat f;
	int			flag;
	
	if (lstat(cmd->str[0], &f) != -1)
	{
		flag = f.st_mode & S_IFMT;
		if (flag == S_IFDIR && (cmd->str[0][ft_strlen(cmd->str[0]) - 1] == '/' || ft_strncmp(cmd->str[0], "./", 2) == 0))
		{
			shell->exitcode = 126;
			return (dprintf(2, " Is a directory\n"));
		}
		else if ((f.st_mode & S_IXUSR) && (f.st_mode & S_IRUSR) && (cmd->str[0][0] == '/' || ft_strncmp(cmd->str[0], "./", 2) == 0))
			return(execute_string(shell, cmd, ft_strdup(cmd->str[0]), pipe_fd));
		else if (flag != S_IXUSR && flag != S_IRUSR && flag != S_IFDIR && flag != S_IFLNK)
		{
			shell->exitcode = 126;
			return(dprintf(2, " Permission denied\n"));
		}
	}
	else if (ft_strncmp(cmd->str[0], "./", 2) == 0 || cmd->str[0][0] == '/')
	{
		shell->exitcode = 127;
		return (dprintf(2, " No such file or directory\n"));
	}
	shell->exitcode = 127;
	return (dprintf(2, " command not found\n"));
}


int	execute_cmd(t_shell *shell, t_commands *cmd, int pipe_fd)
{
	char *path;

	(void)pipe_fd;
	path = ft_getenv("PATH");
	if (ft_strcmp2(cmd->str[0], "whoami") && !path)
	{
		shell->exitcode = 127;
		return(printf("No such file or directory\n"));
	}
	free(path);
	if (execute_builtin(shell, cmd, pipe_fd) || execute_binaries(shell, cmd, pipe_fd))
		return (1);
	else
	 	execute_files(shell, cmd, pipe_fd); // check() exec.c
	return (0);
}

// static void	redirect_dup()
// {
	
// }

void	redirect_and_execute(t_shell *shell, t_commands *cmd, int	pipe_fd)
{
	if (cmd->redirection)
		redirection_dup(shell, cmd);
	else
		execute_cmd(shell, cmd, pipe_fd);
}

int	execute(t_shell *shell)
{
	int	fdd;
	int	i;
	t_commands	*cmd = shell->com_struct;

	fdd = dup(0);
	i = 0;
	while (cmd)
	{
		// if (list->pipecell!=NULL)
		// else 
		redirect_and_execute(shell, cmd, 0);
		// free cmd

		cmd = cmd->next;
	}
	return (0);
}
