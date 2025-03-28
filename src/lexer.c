/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:06:43 by ahornstr          #+#    #+#             */
/*   Updated: 2025/03/28 02:55:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_lexer_tools(t_lexer_tools *tools)
{
	tools->buffer = ft_strdup("");
	if (!tools->buffer)
		return (1);
	tools->id = 0;
	tools->mem_size = 0;
	tools->token_len = 0;
	tools->quote_flag = 0;
	tools->quote_type = '\0';
	return (0);
}

int	fin_tok(t_token **lex, t_lexer_tools *tools, t_operators type)
{
	if (tools->token_len > 0)
	{
		if (!tools->buffer)
			tools->buffer = malloc(1);
		if (!tools->buffer)
			return (1);
		tools->buffer[tools->token_len] = '\0';
		if (token_back(lex, c_token(tools->buffer, 0, tools->id++, type)))
			return (1);
		tools->token_len = 0;
	}
	return (0);
}

int	op_token(t_token **lex, t_token **cur, t_lexer_tools *tools)
{
	char	*temp;

	temp = NULL;
	if (fin_tok(lex, tools, O_G_WORD))
		return (1);
	if ((*cur)->str && ((*cur)->token == O_OR || (*cur)->token == O_AND \
	|| (*cur)->token == O_DGREAT || (*cur)->token == O_DLESS))
	{
		temp = ft_strdup((*cur)->str);
		if (!temp)
			return (error_handler("Malloc error @ op_token", 1));
	}
	else
	{
		temp = malloc(sizeof(char) * 2);
		if (!temp)
			return (error_handler("Malloc error @ op_token", 1));
		temp[0] = (*cur)->c;
		temp[1] = '\0';
	}
	if (token_back(lex, c_token(temp, 0, tools->id++, id_op(temp[0], temp[1]))))
		return (free(temp), 1);
	free (temp);
	return (0);
}

int	append_to_buffer(t_lexer_tools *tools, char c)
{
	while (tools->token_len + 1 >= tools->mem_size)
	{
		if (tools->mem_size == 0)
			tools->mem_size += 1;
		else
			tools->mem_size *= 2;
	}
	if (tools->buffer)
		tools->buffer = realloc(tools->buffer, tools->mem_size);
	if (!tools->buffer)
		return (1);
	tools->buffer[tools->token_len++] = c;
	return (0);
}

int	lexer(t_shell *shell)
{
	t_lexer_tools	tools;
	int				err;

	err = 0;
	if (!unclosed_quotes(shell->input))
		return (error_handler("Unclosed quotes", 2));
	shell->tokenized = tokenize_input(shell->input, 0, 0);
	if (!shell->tokenized)
		return (1);
	shell->lex = group_tokens(shell->tokenized, tools, err);
	if (!shell->lex)
		return (1);
	return (0);
}
