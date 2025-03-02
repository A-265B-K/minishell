/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/09 16:30:42 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/03/02 16:28:16 by alkuijte      ########   odam.nl         */
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
	{
	//	dprintf(2, "builtin not executed\n");
		return (0);
	}
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
	{
		execve(str, cmd->str, (char *const *)borrow_env());
		// errpr msg
		exit(127);
	}
	free(str);
	if (pipe_fd)
		return (1);
	if (ft_strcmp2(cmd->str[0], "./minishell"))
		signal(SIGINT, SIG_IGN);
	waitpid(pid, NULL, 0);
	//status_child();
	pid = 0;
	return (1);
}

int	redirection_permission(t_commands *cmd)
{
	t_redirects r;

	r = cmd->redirects;
	//printf("Permissions: %d %d %d\n", r.out_fd, r.in_fd, r.err_fd);
	if ((r.sstdin != NULL && r.in_fd < 0) || (r.sstdout != NULL && r.out_fd < 0) || (r.sstderr != NULL && r.err_fd < 0))
		return (0);
	else
		return (1);
}

int		check_perms(t_shell *shell, t_commands *cmd, char *bin, struct stat statbuf, int pipe_fd)
{
	// if (!cmd->str[1])
	// 	return (1);
	if (statbuf.st_mode & S_IFREG)
	{
		if (statbuf.st_mode & S_IXUSR && redirection_permission(cmd))
			return (execute_string(shell, cmd, bin, pipe_fd));
		else
		{
			//dprintf(2, "minishell: execve: Permission denied\n");
			shell->exitcode = 1;
		}
		free(bin);
		return (1);
	}
	else
	{
		dprintf(2, "minishell: %s : Is a directory\n", cmd->str[1]);
		shell->exitcode = 1;
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


int	execute_cmd(t_shell *shell, t_commands *cmd, int pipe_fd) // make this exit with cmd exitcode
{
	char *path;

	(void)pipe_fd;
	path = ft_getenv("PATH");
	if (!cmd->str)
		cmd->str = (char **)ft_strdup("");
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

static void	clean_redir(t_commands *cmd, int sin, int sout, int serr)
{
	if (cmd->redirects.in_fd)
		dup2(sin, 0);
	if (cmd->redirects.out_fd)
		dup2(sout, 1);
	if (cmd->redirects.err_fd)
		dup2(serr, 2);
}

static void redirection_dup(t_shell *shell, t_commands *cmd)
{
	int	s_stdin;
	int	s_stdout;
	int	s_stderr;

	(void)shell;
	if (!(s_stdin = 0) && cmd->redirects.in_fd >= 0)
	{
		s_stdin = dup(0);
		close(0);
		dup2(cmd->redirects.in_fd, 0);
	}
	if (!(s_stdout = 0) && cmd->redirects.sstdout)
	{
		s_stdout = dup(1);
		close(1);
		dup2(cmd->redirects.out_fd, 1);
	}
	if (!(s_stderr = 0) && cmd->redirects.sstderr)
	{
		s_stderr = dup(2);
		close(2);
		dup2(cmd->redirects.err_fd, 2);
	}
	shell->exitcode = execute_cmd(shell, cmd, 0);
	clean_redir(cmd, s_stdin, s_stdout, s_stderr);
}

static void	execute_child(t_shell *shell, t_commands *cmd, int fd[2], int *pipe_fd)
{
    if (*pipe_fd != 0)
    {
        dup2(*pipe_fd, 0); // copy stdin to read end of prev pipe
        close(*pipe_fd); // close old read end
    }

    if (cmd->next)
    {
        dup2(fd[1], 1); // redirect stdout to write end of new pipe
    }

    close(fd[0]);	// close the pipe
    close(fd[1]);
	//printf("Executed child!\n");
	exit(execute_cmd(shell, cmd, *pipe_fd));
}


int	run_pipe(t_shell *shell, t_commands *cmd, int	pipe_fd)
{
	int fd[2];
	int	pid;

	if (cmd->next && pipe(fd)) // open pipe
		return (-1);
	pid = fork();
	if (pid < 0)	// if pipe fails close all fds
	{
		close(fd[0]);
		close(fd[1]);
		close(pipe_fd);
		return (-1);
	}
	else if (!pid)	// if child execute child process and execute command
	{
		execute_child(shell, cmd, fd, &pipe_fd);
	}
	//printf("Waiting for child\n");
	waitpid(pid, NULL, 0);
//	printf("Finished waiting for child\n");
	if (pipe_fd != 0)
		close(pipe_fd); // close previous read end
	close(fd[1]);	// close write end of new pipe
	return(fd[0]); // return read end of the new pipe
}

void	redirect_and_execute(t_shell *shell, t_commands *cmd, int	pipe_fd)
{
	if (cmd->redirection)
		redirection_dup(shell, cmd);
	else
		execute_cmd(shell, cmd, pipe_fd);
}

void execute_pipe(t_shell *shell, t_commands *cmd)
{
    int pipe_fd = -1;

    while (cmd)
    {
        pipe_fd = run_pipe(shell, cmd, pipe_fd);
	//	printf("Meow2!\n");
        cmd = cmd->next;
    }
    // Wait for all child processes (not shown here, but should be handled)
}

char	*ft_strlcpy2(char *str, int	c)
{
	char *out;
	int		i;

	i = 0;
	out = malloc(ft_strlen(str) - c + 1);
	if (!out)
		return (NULL);
	while (str[c])
		out[i++] = str[c++];
	out[i] = '\0';
	return (out); 
}

void	handle_redirects(t_commands *cmd)
{
	char	*file = NULL;
	int		type;

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
		else	// else
//	wait(&pid);
	//check_child();
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

	if (type == 2)  // Output Redirecshell_ittion (>)
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

	if (type == 3)  // Append Redirection (>>)
	{
		cmd->redirects.sstderr = file;
		cmd->redirects.err_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
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

int	execute(t_shell *shell)
{
	//int	pipe_fd;
	// int	i;
	t_commands	*cmd = shell->com_struct;


	// i = 0;
	if (cmd)
	{
		handle_redirects(cmd);
		if (cmd->next)
			execute_pipe(shell, cmd);
		else // implement security chck
			redirect_and_execute(shell, cmd, 0);
		// free cmd

	//	cmd = cmd->next;
	}
//	printf("Made out of the pipedream\n");
	// close fd
	return (0);
}
