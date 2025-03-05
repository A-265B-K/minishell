/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/05 18:38:10 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/03/05 18:38:27 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_strcmp2(const char *s1, const char *s2) // move to libft
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

char	*ft_strlcpy2(char *str, int	c) // move to libft
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

char *ft_strjoin3(const char *s1, const char *s2, const char *s3) // move to libft
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
		exit(127);
	}
	free(str);
	if (pipe_fd)
		return (1);
	if (ft_strcmp2(cmd->str[0], "./minishell"))
		signal(SIGINT, SIG_IGN);
	waitpid(pid, NULL, 0);
	pid = 0;
	return (0);
}



int		check_perms(t_shell *shell, t_commands *cmd, char *bin, struct stat statbuf, int pipe_fd)
{
	if (statbuf.st_mode & S_IFREG)
	{
		if (statbuf.st_mode & S_IXUSR && redirection_permission(cmd))
			return (execute_string(shell, cmd, bin, pipe_fd));
		else
		{
			dprintf(2, "minishell: execve: Permission denied\n"); // Fix this part, weird errors when using cat + pipe
			return (1);
		}
		free(bin);
		return (1);
	}
	else
	{
		dprintf(2, "minishell: %s : Is a directory\n", cmd->str[1]);
		return (1);
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
		path = strtok_r(NULL, ":", &saveptr);
	}
	free(path_env);
	return (-1);
}

static int	execute_files(t_shell *shell, t_commands *cmd, int pipe_fd)
{
	struct stat f;
	int			flag;
	
	if (lstat(cmd->str[0], &f) != -1)
	{
		flag = f.st_mode & S_IFMT;
		if (flag == S_IFDIR)
		{
			dprintf(2, " Is a directory\n");
			return (126);
		}
		else if ((f.st_mode & S_IXUSR) && (f.st_mode & S_IRUSR) && (cmd->str[0][0] == '/' || ft_strncmp(cmd->str[0], "./", 2) == 0))
			return(execute_string(shell, cmd, ft_strdup(cmd->str[0]), pipe_fd));
		else if (flag != S_IXUSR && flag != S_IRUSR && flag != S_IFDIR && flag != S_IFLNK && ft_strncmp(cmd->str[0], "./", 2) == 0)
		{
			dprintf(2, " Permission denied\n");
			return(126);
		}
	}
	else if (ft_strncmp(cmd->str[0], "./", 2) == 0 || cmd->str[0][0] == '/')
	{
		dprintf(2, " No such file or directory\n");
		return (127);
	}
	dprintf(2, " command not found\n");
	return (127);
}


int	execute_cmd(t_shell *shell, t_commands *cmd, int pipe_fd) // make this exit with cmd exitcode
{
	char *path;
	int	exitcode;

	path = getcwd(NULL, 0);
	if (!cmd->str)
		cmd->str = (char **)ft_strdup("");
	if (ft_strcmp2(cmd->str[0], "whoami") && !path)
	{
		dprintf(2, "No such file or directory\n");
		return(127);
	}
	else if (!ft_strcmp2(cmd->str[0], path))
	{
		dprintf(2, " Is a directory\n");
		return (126);
	}
	free(path);
	exitcode = execute_builtin(shell, cmd);
	if (exitcode == -1)
		exitcode = execute_binaries(shell, cmd, pipe_fd);
	if (exitcode == -1)
	 	exitcode = execute_files(shell, cmd, pipe_fd);
	return (exitcode);
}

int	execute(t_shell *shell)
{
	t_commands	*cmd = shell->com_struct;

	if (cmd)
	{
		handle_redirects(cmd);
		if (cmd->next)
			execute_pipe(shell, cmd);
		else // implement security check
			shell->exitcode = redirect_and_execute(shell, cmd, 0);
	}
	// close fd
	return (0);
}
