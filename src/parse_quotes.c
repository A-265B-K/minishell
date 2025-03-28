/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 21:51:19 by marvin            #+#    #+#             */
/*   Updated: 2025/03/27 21:51:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_exitcode(char **result, t_q *q, t_shell *shell, char *s)
{
	int		new_size;
	int		len;
	char	*exitcode_str;

	exitcode_str = ft_itoa(shell->exitcode);
	if (!exitcode_str)
		return (1);
	len = ft_strlen(exitcode_str);
	new_size = q->j + len + ft_strlen(s) + 1;
	*result = realloc(*result, new_size);
	if (!*result)
	{
		free(exitcode_str);
		return (1);
	}
	memcpy(&(*result)[q->j], exitcode_str, len);
	q->j += len;
	q->i += 1;
	free(exitcode_str);
	return (0);
}

void	toggle_quotes(char c, t_q *q)
{
	if (c == '\'' && !(q->in_d))
		q->in_s = !(q->in_s);
	else if (c == '"' && !(q->in_s))
		q->in_d = !(q->in_d);
}

void	init_q(t_q *q)
{
	q->in_s = 0;
	q->in_d = 0;
	q->i = 0;
	q->j = 0;
}

int	handle_exp(char *input, char **result, t_shell *shell, t_q *q)
{
	if (input[q->i + 1] == '?')
	{
		if (handle_exitcode(result, q, shell, input))
			return (1);
	}
	else if (!variable_expansion(input, result, q, shell))
		return (1);
	return (0);
}

void	handle_regular_char(const char *input, char **result, t_q *q)
{
	(*result)[q->j] = input[q->i];
	q->j++;
}
