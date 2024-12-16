/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahornstr <ahornstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:40:38 by ahornstr          #+#    #+#             */
/*   Updated: 2024/11/20 16:41:10 by ahornstr         ###   ########.fr       */
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


char	*recursive_strcat(char **strs)
{
	size_t	len;
	char	**temp;
	char	*res;

	len = 0;
	temp = strs;

	while (*temp)
		len += strlen(*temp++);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	res[0] = '\0';
	while (*strs)
		strcat(res, *strs++);
	return (res);
}

char **get_function_name(const char *str)
{
	size_t len;
	char **out;

	out = malloc(2 * sizeof(char *));
	if (!out)
		return (NULL);
	bzero(out, 2);
	len = 0;
	while (str[len] && str[len] != ' ')
		len++;
	out[0] = malloc(len + 1);
	out[1] = malloc(strlen(str) - len);
	if (!out[0] || !out[1])
	{
		free(out[0]);
		free(out[1]);
		free(out);
		return (NULL);
	}
	strncpy(out[0], str, len);
	out[0][len] = '\0';
	if (strlen(str) > len)
		strcpy(out[1], str + len + 1);
	else
	{
		free(out[1]);
		out[1] = NULL;
	}
	return (out);
}
