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

int	quote_group(t_token **current, t_lexer_tools *tools, t_token **lex)
{
	(void)lex;
	tools->quote_type = (*current)->c;
	append_to_buffer(tools, (*current)->c);
	(*current) = (*current)->next;
	while ((*current) && group_quotes(&(*current), tools->quote_type))
	{
		append_to_buffer(tools, (*current)->c);
		(*current) = (*current)->next;
	}
	if ((*current) && ((*current)->c == tools->quote_type \
	|| (*current)->c == tools->quote_type))
	{
		append_to_buffer(tools, (*current)->c);
		(*current) = (*current)->next;
		return (0);
	}
	return (1);
}

t_token	*group_tokens(t_token *lexer_input)
{
	t_token			*lex;
	t_token			*current;
	t_lexer_tools	tools;

	current = lexer_input;
	lex = NULL;
	init_lexer_tools(&tools);
	while (current)
	{
		if (current->c == '\'' || current->c == '\"')
		{
			if (!quote_group(&current, &tools, &lex))
				continue ;
		}
		if (current && isspace(current->c))
			finalize_token(&lex, &tools, O_G_WORD);
		else if (current && is_f_operator(current->c))
			op_token(&lex, &current, &tools);
		else if (current)
			append_to_buffer(&tools, current->c);
		current = current->next;
	}
	finalize_token(&lex, &tools, O_G_WORD);
    free (tools.buffer);
	return (lex);
}
