/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:40:38 by ahornstr          #+#    #+#             */
/*   Updated: 2025/03/28 02:31:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*mem_add(size_t count, size_t size)
{
	char	*ptr;
	int		i;

	i = size * count;
	ptr = malloc(i + 1);
	if (!ptr)
		exit(error_handler("Malloc error @ mem_add", 1));
	while (i >= 0)
		ptr[i--] = '\0';
	return ((void *) ptr);
}

char	**alloc_double(char **envp)
{
	char	**new;
	int		i;

	new = mem_add(ft_strarrlen(envp) + 1, sizeof(char *));
	i = 0;
	while (envp[i])
	{
		new[i] = ft_strdup(envp[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

int	ft_strarrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	free_double(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*free_join(char *s1, char *s2, bool free_s1, bool free_s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	if (free_s2 == true)
		free(s2);
	if (free_s1 == true)
		free(s1);
	return (tmp);
}
