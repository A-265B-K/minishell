/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:08:01 by elie              #+#    #+#             */
/*   Updated: 2024/07/06 10:12:05 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	gnl_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*gnl_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[gnl_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

void	gnl_strjoin(char **buffer, char *recently_read)
{
	int		i;
	int		j;
	int		len;
	char	*new_str;

	len = gnl_strlen(*buffer) + gnl_strlen(recently_read) + 1;
	new_str = ft_calloc(len, sizeof(char));
	if (!new_str)
		return (ft_free_and_null(buffer));
	i = 0;
	while ((*buffer)[i])
	{
		new_str[i] = (*buffer)[i];
		i++;
	}
	j = 0;
	while (recently_read[j])
	{
		new_str[i + j] = recently_read[j];
		j++;
	}
	ft_free_and_null(buffer);
	*buffer = new_str;
	return ;
}
