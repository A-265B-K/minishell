/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahornstr <ahornstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:17:43 by ahornstr          #+#    #+#             */
/*   Updated: 2025/01/21 15:48:24 by ahornstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_token *create_token(char *str, char c, int id, t_operators token)
{
    t_token *new_token;
    
	new_token = malloc(sizeof(t_token));
    if (!new_token)
        return NULL;
    if (str)
    	new_token->str = ft_strdup(str);
	else
		new_token->str = NULL;
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

    while (head)
	{
		if (head->str)
			free (head->str);
        temp = head;
        head = head->next;
        free(temp);
    }
}

int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '&')
		return (1);
	return (0);
}

int is_f_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}


