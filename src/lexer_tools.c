/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahornstr <ahornstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:17:43 by ahornstr          #+#    #+#             */
/*   Updated: 2024/12/10 16:36:24 by ahornstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(t_shell *shell, int id, t_operators token)
{
	t_token *new_token = mem_add(sizeof(t_token), 1);
	new_token->c = shell->input[id];
	new_token->id = id;
	new_token->token = token;
	new_token->next = NULL;
	new_token->prev = NULL;
	return new_token;
}

void	token_add_back(t_shell *shell, t_token *new_token)
{
	t_token	*current;
	if (!shell->tokenized)
		shell->tokenized = new_token;
	else
	{
		current = shell->tokenized;
		while (current->next)
			current = current->next;
		current->next = new_token;
		new_token->prev = current;
	}
}


