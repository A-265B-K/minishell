/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahornstr <ahornstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:40:38 by ahornstr          #+#    #+#             */
/*   Updated: 2024/12/02 14:39:59 by ahornstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*mem_add(size_t count, size_t size)
{
	char	*ptr;
	int		n;

	n = size * count;
	ptr = malloc(n + 1);
	if (!ptr)
		exit(error(ERR_MALLOC));
	while (n >= 0)
		ptr[n--] = '\0';
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

