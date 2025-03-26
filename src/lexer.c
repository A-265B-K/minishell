/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:06:43 by ahornstr          #+#    #+#             */
/*   Updated: 2025/03/26 01:34:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_lexer_tools(t_lexer_tools *tools)
{
	tools->buffer = NULL;
	tools->id = 0;
	tools->mem_size = 0;
	tools->token_len = 0;
	tools->quote_flag = 0;
	tools->quote_type = '\0';
}

void	finalize_token(t_token **lex, t_lexer_tools *tools, t_operators type)
{
	if (tools->token_len > 0)
	{
		if (!tools->buffer)
			tools->buffer = malloc(1);
        if (!tools->buffer)
            return ;
		tools->buffer[tools->token_len] = '\0';
		token_back(lex, c_token(tools->buffer, 0, tools->id++, type));
		tools->token_len = 0;
	}
}

void	op_token(t_token **lex, t_token **current, t_lexer_tools *tools)
{
	char	*temp;

	temp = NULL;
	finalize_token(lex, tools, O_G_WORD);
	if ((*current)->str && ((*current)->token == O_OR \
	|| (*current)->token == O_AND \
	|| (*current)->token == O_DGREAT \
	|| (*current)->token == O_DLESS))
	{
		temp = ft_strdup((*current)->str);
		if (!temp)
			error("malloc error handle operator token\n");
	}
	else
	{
		temp = malloc(sizeof(char) * 2);
        if (!temp)
            error("malloc op_token");
		temp[0] = (*current)->c;
        temp[1] = '\0';
	}
	token_back(lex, c_token(temp, 0, tools->id++, id_op(temp[0], temp[1])));
    if (temp)
	    free (temp);
}

void	append_to_buffer(t_lexer_tools *tools, char c)
{
	while (tools->token_len + 1 >= tools->mem_size)
	{
		if (tools->mem_size == 0)
			tools->mem_size += 1;
		else
			tools->mem_size *= 2;
	}
	if (tools->buffer)
	{
		tools->buffer = realloc(tools->buffer, tools->mem_size);
	}
	else
		tools->buffer = mem_add(tools->mem_size, sizeof(char));
	if (!tools->buffer)
		return ;
	tools->buffer[tools->token_len++] = c;
}

int	lexer(t_shell *shell)
{
	if (!unclosed_quotes(shell->input))
	{
		error("Unclosed quotes\n");
		return (0);
	}
	shell->tokenized = tokenize_input(shell->input);
	// print_tokens(shell->tokenized);
	shell->lex = group_tokens(shell->tokenized);
	// print_grouped(shell->lex);
	return (1);
}
