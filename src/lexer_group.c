/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_group.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:52:41 by marvin            #+#    #+#             */
/*   Updated: 2025/03/19 17:52:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	group_quotes(t_token **current, char c)
{
	if (((*current)->c != c))
		return (1);
	return (0);
}

int	quote_group(t_token **current, t_lexer_tools *tools)
{
	tools->quote_type = (*current)->c;
	if (append_to_buffer(tools, (*current)->c))
		return (1);
	(*current) = (*current)->next;
	while ((*current) && group_quotes(&(*current), tools->quote_type))
	{
		if (append_to_buffer(tools, (*current)->c))
			return (1);
		(*current) = (*current)->next;
	}
	if ((*current) && ((*current)->c == tools->quote_type \
	|| (*current)->c == tools->quote_type))
	{
		if (append_to_buffer(tools, (*current)->c))
			return (1);
		(*current) = (*current)->next;
		return (0);
	}
	return (-1);
}

int	build_group(t_token *current, t_token **lex, t_lexer_tools *tools)
{
	int	err;

	err = 0;
	if (current && ft_isspace(current->c))
		err = fin_tok(lex, tools, O_G_WORD);
	else if (current && is_f_operator(current->c))
		err = op_token(lex, &current, tools);
	else if (current)
		err = append_to_buffer(tools, current->c);
	if (err && tools->buffer)
		free(tools->buffer);
	return (err);
}

t_token	*group_tokens(t_token *lexer_input, t_lexer_tools tools, int err)
{
	t_token			*lex;
	t_token			*current;

	current = lexer_input;
	lex = NULL;
	if (init_lexer_tools(&tools))
		return (NULL);
	while (current)
	{
		if (current->c == '\'' || current->c == '\"')
		{
			err = quote_group(&current, &tools);
			if (err == 0)
				continue ;
			if (err == 1)
				return (NULL);
		}
		if (build_group(current, &lex, &tools))
			return (NULL);
		current = current->next;
	}
	if (fin_tok(&lex, &tools, O_G_WORD))
		return (free(tools.buffer), NULL);
	free(tools.buffer);
	return (lex);
}
