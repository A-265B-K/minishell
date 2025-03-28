/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:58:56 by marvin            #+#    #+#             */
/*   Updated: 2025/03/27 20:58:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**duplicate_envp(char **envp, int count)
{
	char	**new_envp;
	int		i;

	new_envp = malloc(sizeof(char *) * (count + 1));
	i = 0;
	while (i < count)
	{
		new_envp[i] = envp[i];
		i++;
	}
	new_envp[count] = NULL;
	return (new_envp);
}

void	sort_envp(char **sorted_envp, int count)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (strcmp(sorted_envp[i], sorted_envp[j]) > 0)
			{
				temp = sorted_envp[i];
				sorted_envp[i] = sorted_envp[j];
				sorted_envp[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	print_env_sorted(char **envp)
{
	int		count;
	char	**sorted_envp;
	int		i;

	i = 0;
	count = count_env_vars(envp);
	sorted_envp = duplicate_envp(envp, count);
	sort_envp(sorted_envp, count);
	while (sorted_envp[i])
	{
		printf("declare -x %s\n", sorted_envp[i]);
		i++;
	}
	free(sorted_envp);
}

int	get_var_name_len(char *new_var)
{
	int	len;

	len = 0;
	while (new_var[len] && new_var[len] != '=')
		len++;
	return (len);
}

int	find_var_index(char **envp, char *new_var, int len)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], new_var, len) == 0 && envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}
