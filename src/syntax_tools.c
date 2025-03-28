/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 21:56:02 by marvin            #+#    #+#             */
/*   Updated: 2025/03/27 21:56:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	if (!c)
		return (0);
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	else if (c == '\v' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	ft_isquote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	unclosed_quotes(const char *input)
{
	char	open_quote;
	int		i;

	i = 0;
	open_quote = '\0';
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			if (open_quote == '\0')
				open_quote = input[i];
			else if (open_quote == input[i])
				open_quote = '\0';
		}
		i++;
	}
	if (open_quote != '\0')
		return (0);
	return (1);
}

int	check_hd(char *str)
{
	if (str && str[0])
	{
		if (str[0] == '<' && str[1] == '<')
			return (0);
		else if (is_f_operator(str[0]))
			return (1);
	}
	return (0);
}

int	valid_combo(char *str, int i)
{
	char	*temp;

	temp = ft_substr(str, i, 2);
	if (!temp)
		return (0);
	if (ft_strcmp(temp, "<<") == 0 || ft_strcmp(temp, ">>") == 0 \
		|| ft_strcmp(temp, "||") == 0)
	{
		free (temp);
		return (1);
	}
	free (temp);
	return (0);
}
