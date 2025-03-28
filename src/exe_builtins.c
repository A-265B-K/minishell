/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:00:32 by marvin            #+#    #+#             */
/*   Updated: 2025/03/23 14:00:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_pwd(t_shell *shell)
{
	char	*temp;

	temp = ft_env_get("PWD", shell->envp);
	if (!temp)
		return (error_handler("Malloc error @ ft_pwd", 1));
	printf("%s\n", temp);
	free (temp);
	return (0);
}

int	is_flag(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **params)
{
	int	flag;
	int	i;

	flag = 1;
	i = 0;
	if (!params || !params[i])
		return (0);
	while (params[i] && is_flag(params[i]))
	{
		flag = 0;
		i++;
	}
	while (params[i])
	{
		if (params[i][0])
		{
			printf("%s", params[i]);
			if (params[i + 1] && params[i][0])
				printf(" ");
		}
		i++;
	}
	if (flag > 0)
		printf("\n");
	return (0);
}

int	ft_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
	{
		printf("%s\n", shell->envp[i]);
		i++;
	}
	return (0);
}

int	execute_builtin(t_shell *shell, t_commands *cmd)
{
	if (!ft_strcmp2(cmd->builtin, "pwd"))
		return (ft_pwd(shell));
	else if (!ft_strcmp2(cmd->builtin, "echo"))
		return (ft_echo(cmd->str));
	else if (!ft_strcmp2(cmd->builtin, "cd"))
		return (ft_cd(cmd->str, &shell->envp, shell));
	else if (!ft_strcmp2(cmd->builtin, "export"))
		return (ft_export(cmd->str, &shell->envp));
	else if (!ft_strcmp2(cmd->builtin, "unset"))
		return (ft_unsetenv(cmd->str, shell));
	else if (!ft_strcmp2(cmd->builtin, "env"))
		return (ft_env(shell));
	else if (!ft_strcmp2(cmd->builtin, "exit"))
		ft_exit(cmd->str, shell->exitcode);
	return (-1);
}
