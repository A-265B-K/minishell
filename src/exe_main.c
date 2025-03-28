/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:52:39 by marvin            #+#    #+#             */
/*   Updated: 2025/03/26 17:52:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_absolute_path(char *cmd)
{
	struct stat	st;

	if (stat(cmd, &st) == -1)
	{
		errno = ENOENT;
		return (NULL);
	}
	if (S_ISDIR(st.st_mode))
	{
		errno = EISDIR;
		return (NULL);
	}
	if (access(cmd, X_OK) == -1)
	{
		errno = EACCES;
		return (NULL);
	}
	return (ft_strdup(cmd));
}

char	*get_command_path(char *cmd, t_shell *shell)
{
	char		*path;
	char		*full_path;
	char		*dir;
	struct stat	st;

	if (ft_strchr(cmd, '/'))
		return (check_absolute_path(cmd));
	path = ft_env_get("PATH", shell->envp);
	if (!path)
		return (NULL);
	dir = ft_strtok(path, ":");
	while (dir)
	{
		full_path = ft_strjoin3(dir, "/", cmd);
		if (!full_path)
			return (free(path), NULL);
		if (stat(full_path, &st) == 0 && !S_ISDIR(st.st_mode))
			if (access(full_path, X_OK) == 0)
				return (free(path), full_path);
		free(full_path);
		dir = ft_strtok(NULL, ":");
	}
	free(path);
	return (NULL);
}

int	is_single_builtin(t_shell *shell)
{
	if (shell->com_struct->next != NULL)
		return (0);
	if (shell->com_struct->builtin == NULL)
		return (0);
	if (ft_strcmp(shell->com_struct->builtin, "exit") == 0)
		return (1);
	if (shell->com_struct->redirection != NULL)
		return (0);
	return (1);
}

void	execute_external(t_commands *cmd, t_shell *shell)
{
	char	*full_path;
	char	**env_array;

	rm_empty_str(cmd);
	if (!cmd->str || !cmd->str[0])
		exit (0);
	full_path = get_command_path(cmd->str[0], shell);
	if (!full_path)
		path_error(cmd);
	env_array = env_to_array(shell);
	if (!env_array)
	{
		free(full_path);
		exit(1);
	}
	execve(full_path, cmd->str, env_array);
	if (errno == ENOEXEC)
		ft_non_binary(full_path, env_array);
	perror("minishell");
	free(full_path);
	free_double(env_array);
	exit(126);
}

int	execute(t_shell *shell)
{
	if (is_single_builtin(shell))
	{
		shell->exitcode = execute_builtin(shell, shell->com_struct);
		return (shell->exitcode);
	}
	shell->exitcode = execute_pipes(shell);
	return (shell->exitcode);
}
