/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 21:27:58 by marvin            #+#    #+#             */
/*   Updated: 2025/03/27 21:27:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_tempfile(t_shell *shell)
{
	char	*str;
	int		fd;

	str = free_join("/tmp/heredoc", ft_itoa(shell->heredoc_id), 0, 1);
	fd = open(str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return (NULL);
	close(fd);
	return (str);
}

int	write_to_tempfile(const char *filename, const char *content)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_TRUNC);
	if (fd == -1)
		return (error_handler("invalid fd @ write_to_tempfile", 1));
	write(fd, content, ft_strlen(content));
	close(fd);
	return (0);
}
