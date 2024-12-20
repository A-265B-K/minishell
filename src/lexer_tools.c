/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:17:43 by ahornstr          #+#    #+#             */
/*   Updated: 2024/12/20 10:40:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *create_token(char c, int id, t_operators token)
{
    t_token *new_token;
	new_token = malloc(sizeof(t_token));
    if (!new_token)
        return NULL;
    new_token->c = c;
    new_token->id = id;
    new_token->token = token;
    new_token->next = NULL;
    new_token->prev = NULL;
    return (new_token);
}

void token_add_back(t_token **head, t_token *new_token)
{
    t_token *temp;
	if (!*head)
	{
        *head = new_token;
        return;
    }
    temp = *head;
    while (temp->next)
        temp = temp->next;
    temp->next = new_token;
    new_token->prev = temp;
}

void	free_tokens(t_token *head)
{
    t_token *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}


