/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:18:20 by marvin            #+#    #+#             */
/*   Updated: 2025/03/22 13:18:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	execute_string(t_shell *shell, t_commands *cmd, char *str, int pipe_fd)
{
	pid_t	pid;

	(void)shell;
    pid = 0;
	if (!pipe_fd)
		pid = fork();
	if (!pipe_fd && pid < 0)
	{
		free(str);
		return (error_handler("execve: failed to fork", -1));
	}
	else if (!pid)
	{
    //     printf(" - executing @execute_string - \n");
    //     printf("execve(str, cmd->str, envp)\n[str = %s]\n", str);
    //     printf("cmd->str = \n");
        // print_array(cmd->str);
        execve(str, cmd->str, shell->envp);
        // printf("passed execve\n");
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

int	check_perms(t_shell *shell, t_commands *cmd, char *bin, \
				struct stat statbuf, int pipe_fd)
{
	if (statbuf.st_mode & S_IFREG)
	{
		if (statbuf.st_mode & S_IXUSR && redirection_permission(cmd))
			return (execute_string(shell, cmd, bin, pipe_fd));
		else	// Fix this part, weird errors when using cat + pipe
			return (error_handler("minishell: execve: Permission denied", 1));
		free(bin);
		return (1);
	}
	else
	{
		dprintf(2, "minishell: %s : Is a directory\n", cmd->str[0]);
		return (1);
	}
	free(bin);
	return (1);
}

int	execute_binaries(t_shell *shell, t_commands *cmd, int pipe_fd)
{
	struct stat	statbuf;
	char		*path_env;
	char		*path;
	char		*bin;
	char		*saveptr;

	path_env = ft_getenv("PATH", shell);
	if (!path_env || !*path_env)
		return (-1);
	path = strtok_r(path_env, ":", &saveptr);
	while (path)
	{
		bin = ft_strjoin3(path, "/", cmd->str[0]);
        // printf("bin = %s\n", bin);
		if (lstat(bin, &statbuf) == 0)
		{
			if (access(bin, X_OK) == 0)
			{
				free(path_env);
				return (execute_string(shell, cmd, bin, pipe_fd));
			}
		}
		free(bin);
		path = strtok_r(NULL, ":", &saveptr);
	}
	free(path_env);
	return (-1);
}


static int	execute_files(t_shell *shell, t_commands *cmd, int pipe_fd)
{
	struct stat	f;
	int			flag;

	if (lstat(cmd->str[0], &f) != -1)
	{
		flag = f.st_mode & S_IFMT;
		if (cmd->str[0][0] == '/' || !ft_strncmp(cmd->str[0], "./", 2))
		{
			if (flag == S_IFDIR)
				return (error_handler(" Is a directory", 126));
			else if ((f.st_mode & S_IXUSR) && (f.st_mode & S_IRUSR))
				return (execute_string(shell, cmd, ft_strdup(cmd->str[0]), pipe_fd));
			else if (flag != S_IXUSR && flag != S_IRUSR && flag != S_IFDIR && flag != S_IFLNK)
				return (error_handler(" Permission denied", 126));
		}
	}
	else if (ft_strncmp(cmd->str[0], "./", 2) == 0 || cmd->str[0][0] == '/')
    {
        // printf("erroring man\n");
		return (error_handler(" No such file or directory", 127));
    }
	return (error_handler(" command not found", 127));
}


int	execute_cmd(t_shell *shell, t_commands *cmd, int pipe_fd)
{
	int	exitcode;

	exitcode = execute_builtin(shell, cmd);
	if (exitcode == -1)
    {
        // printf("1\n");
		exitcode = execute_binaries(shell, cmd, pipe_fd);
        // printf("exit after binary = %d\n", exitcode);
    }
	if (exitcode == -1)
    {
        // printf("2\n");
	 	exitcode = execute_files(shell, cmd, pipe_fd);
    }
    // printf("exitcode = %d\n", exitcode);
	return (exitcode);
}

int	execute(t_shell *shell)
{
	t_commands	*cmd;

	cmd = shell->com_struct;
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