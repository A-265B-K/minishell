/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:52:37 by marvin            #+#    #+#             */
/*   Updated: 2025/03/27 20:52:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)(*s1) - (unsigned char)(*s2));
}

int	ft_strcmp2(const char *s1, const char *s2)
{
	if (!s1 || !s2)
	{
		if (s1)
			return (1);
		else if (s2)
			return (-1);
		else
			return (0);
	}
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return ((unsigned char)(*s1) - (unsigned char)(*s2));
		s1++;
		s2++;
	}
	return ((unsigned char)(*s1) - (unsigned char)(*s2));
}

char	*ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
	char	*res;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1;
	res = malloc(len);
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, len);
	ft_strlcat(res, s2, len);
	ft_strlcat(res, s3, len);
	return (res);
}

char	*ft_strlcpy2(char *str, int c)
{
	char	*out;
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

char	**env_to_array(t_shell *shell)
{
	char	**array;
	int		count;
	int		i;

	count = 0;
	while (shell->envp[count])
		count++;
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (i < count)
	{
		array[i] = ft_strdup(shell->envp[i]);
		if (!array[i])
		{
			while (i > 0)
				free(array[--i]);
			free(array);
			return (NULL);
		}
		i++;
	}
	array[i] = NULL;
	return (array);
}
