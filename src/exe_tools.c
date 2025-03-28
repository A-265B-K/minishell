/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:11:16 by marvin            #+#    #+#             */
/*   Updated: 2025/03/23 14:11:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_non_binary(char *full_path, char **envp)
{
	char	**non_bin;

	non_bin = (char **)malloc(sizeof(char *) * 3);
	if (!non_bin)
		return ;
	non_bin[0] = malloc(sizeof(char) * 8);
	if (!non_bin[0])
	{
		free (non_bin);
		return ;
	}
	ft_strlcpy(non_bin[0], "/bin/sh", 8);
	non_bin[1] = ft_strdup(full_path);
	if (!non_bin[1])
	{
		free (non_bin[0]);
		free (non_bin);
		return ;
	}
	non_bin[2] = NULL;
	execve("/bin/sh", non_bin, envp);
	free_double(non_bin);
}

static int	is_delim(char c, const char *delim)
{
	while (*delim)
	{
		if (c == *delim++)
			return (1);
	}
	return (0);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*save;
	char		*token;

	if (str)
		save = str;
	if (!save || !*save)
	{
		save = NULL;
		return (NULL);
	}
	while (*save && is_delim(*save, delim))
		save++;
	if (!*save)
	{
		save = NULL;
		return (NULL);
	}
	token = save;
	while (*save && !is_delim(*save, delim))
		save++;
	if (*save)
		*save++ = '\0';
	else
		save = NULL;
	return (token);
}

void	rm_empty_str(t_commands *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!cmd || !cmd->str)
		return ;
	while (cmd->str[i])
	{
		if (cmd->str[i][0] != '\0')
			cmd->str[j++] = cmd->str[i];
		else
			free(cmd->str[i]);
		i++;
	}
	cmd->str[j] = NULL;
}
