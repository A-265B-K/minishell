/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:18:58 by marvin            #+#    #+#             */
/*   Updated: 2025/03/21 12:18:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_hd(char *line, t_shell *shell, int quoted, char *content)
{
	char	*expanded;

	if (!quoted)
	{
		expanded = expand_quotes(line, shell);
		if (!expanded)
			return (NULL);
		content = free_join(content, expanded, true, false);
		if (!content)
			return (free(expanded), NULL);
		free(expanded);
	}
	else
	{
		content = free_join(content, line, true, false);
		if (!content)
			return (NULL);
	}
	return (content);
}

static char	*read_heredoc_content(const char *lim, int quoted, t_shell *shell)
{
	char	*line;
	char	*content;

	line = NULL;
	content = ft_strdup("");
	while (1)
	{
		free(line);
		line = readline("> ");
		if (!line)
		{
			return (free(content), NULL);
		}
		if (ft_strncmp(line, lim, ft_strlen(lim)) == 0 \
		&& line[ft_strlen(lim)] == '\0')
			return (free(line), content);
		content = expand_hd(line, shell, quoted, content);
		if (!content)
			return (free(line), NULL);
		content = free_join(content, "\n", true, false);
		if (!content)
			return (free(line), NULL);
	}
	return (content);
}

int	hd_to_cmd(t_commands *cmd, char *file_name)
{
	cmd->redirection = realloc(cmd->redirection, sizeof(char *) * \
	(cmd->red_count + 2));
	if (!cmd->redirection)
	{
		free (file_name);
		return (1);
	}
	cmd->redirection[cmd->red_count] = ft_strjoin("<", file_name);
	cmd->redirection[cmd->red_count + 1] = NULL;
	cmd->red_count++;
	free (file_name);
	return (0);
}

char	*check_hd_quote(char *lim, t_shell *shell)
{
	shell->quoted = 0;
	if ((lim[0] == '\'' || lim[0] == '"') && \
	lim[ft_strlen(lim) - 1] == lim[0])
	{
		shell->quoted = 1;
		lim = ft_substr(lim, 1, ft_strlen(lim) - 2);
	}
	else
		lim = ft_strdup(lim);
	return (lim);
}

int	handle_heredoc(t_commands *cmd, t_token *token, t_shell *shell)
{
	char	*delimiter;
	char	*content;
	char	*file_name;

	delimiter = token->str;
	delimiter = check_hd_quote(delimiter, shell);
	if (!delimiter)
		return (1);
	file_name = create_tempfile(shell);
	if (!file_name)
		return (free(delimiter), 1);
	content = read_heredoc_content(delimiter, shell->quoted, shell);
	free (delimiter);
	if (!content)
		return (free(file_name), 1);
	if (write_to_tempfile(file_name, content))
	{
		free(file_name);
		return (free(content), 1);
	}
	if (hd_to_cmd(cmd, file_name))
		return (free(content), 1);
	free(content);
	return (0);
}
