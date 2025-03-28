/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:55:48 by marvin            #+#    #+#             */
/*   Updated: 2025/03/27 20:55:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_new_var(char **envp, char *new_var, int count)
{
	char	**new_envp;
	int		i;

	new_envp = malloc(sizeof(char *) * (count + 2));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_envp[i] = envp[i];
		i++;
	}
	new_envp[i] = ft_strdup(new_var);
	new_envp[i + 1] = NULL;
	return (new_envp);
}

int	count_env_vars(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

int	valid_id_check(const char *name)
{
	int	i;
	int	alph_flag;

	i = 0;
	alph_flag = 0;
	if (!name[0])
		return (0);
	if (name[0] == '=')
		return (0);
	while (name[i] && name[i] != '=')
	{
		if ((name[i] >= 'a' && name[i] <= 'z') || \
		(name[i] >= 'A' && name[i] <= 'Z'))
			alph_flag = 1;
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	if (!alph_flag)
		return (0);
	return (1);
}

int	set_env_var(char ***envp, char *new_var)
{
	int		len;
	int		id;
	char	**new_envp;

	if (!new_var || !valid_id_check(new_var))
		return (ft_putstr_fd(" not a valid identifier\n", STDERR_FILENO), 1);
	len = get_var_name_len(new_var);
	id = find_var_index(*envp, new_var, len);
	if (id != -1)
	{
		free((*envp)[id]);
		(*envp)[id] = ft_strdup(new_var);
		return (1);
	}
	else
	{
		new_envp = add_new_var(*envp, new_var, count_env_vars(*envp));
		if (!new_envp)
			return (error_handler("malloc fail", 1));
		free(*envp);
		*envp = new_envp;
	}
	return (0);
}

int	ft_export(char **cmd, char ***envp)
{
	int	i;
	int	exitcode;

	exitcode = 0;
	i = 0;
	if (!cmd || !cmd[0])
		print_env_sorted(*envp);
	else
	{
		while (cmd[i])
		{
			exitcode = set_env_var(envp, cmd[i]);
			i++;
		}
	}
	return (exitcode);
}
