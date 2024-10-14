/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:03:20 by elie              #+#    #+#             */
/*   Updated: 2024/07/11 11:25:30 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	read_to_buffer(int fd, char **buffer)
{
	int		bytes_read;
	char	*recently_read;

	recently_read = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (recently_read == NULL)
		return (ft_free_and_null(buffer));
	bytes_read = 1;
	while (bytes_read != 0 && !gnl_strchr(*buffer, '\n'))
	{
		bytes_read = read(fd, recently_read, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			ft_free_and_null(&recently_read);
			ft_free_and_null(buffer);
			return ;
		}
		recently_read[bytes_read] = '\0';
		gnl_strjoin(buffer, recently_read);
		if (!*buffer)
			return (ft_free_and_null(&recently_read));
	}
	return (ft_free_and_null(&recently_read));
}

void	extract_line_from_buffer(char **line, char **buffer)
{
	int		i;
	char	*new_line;

	if (*buffer == NULL || (*buffer)[0] == '\0')
		return ;
	i = 0;
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	if ((*buffer)[i] == '\n')
		i++;
	new_line = ft_calloc((i + 1), sizeof(char));
	if (!new_line)
		return (ft_free_and_null(buffer));
	i = 0;
	while ((*buffer)[i] && (*buffer)[i] != '\n')
	{
		new_line[i] = (*buffer)[i];
		i++;
	}
	if ((*buffer)[i] == '\n')
		new_line[i] = '\n';
	*line = new_line;
}

void	update_buffer(char **line, char **buffer)
{
	char	*new_buffer;
	int		i;
	int		j;

	if (!*line)
		return (ft_free_and_null(buffer));
	i = 0;
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	if (!(*buffer)[i])
		return (ft_free_and_null((buffer)));
	if ((*buffer)[0] == '\n')
		i = 0;
	new_buffer = ft_calloc((gnl_strlen(*buffer) - i + 1), sizeof(char));
	if (!new_buffer)
		return (ft_free_and_null(line), ft_free_and_null(buffer));
	j = 0;
	i++;
	while ((*buffer)[i])
		new_buffer[j++] = (*buffer)[i++];
	ft_free_and_null(buffer);
	*buffer = new_buffer;
	return ;
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (ft_free_and_null(&buffer), NULL);
	line = NULL;
	if (!buffer)
		buffer = ft_calloc(1, sizeof(char));
	if (!buffer)
		return (NULL);
	read_to_buffer(fd, &buffer);
	extract_line_from_buffer(&line, &buffer);
	update_buffer(&line, &buffer);
	return (line);
}
