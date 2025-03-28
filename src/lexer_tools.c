/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:17:43 by ahornstr          #+#    #+#             */
/*   Updated: 2025/03/28 00:51:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*c_token(char *str, char c, int id, t_operators token)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	if (str)
	{
		new_token->str = ft_strdup(str);
		if (!new_token->str)
			return (NULL);
	}
	else
		new_token->str = NULL;
	new_token->c = c;
	new_token->id = id;
	new_token->token = token;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

int	token_back(t_token **head, t_token *new_token)
{
	t_token	*temp;

	if (!head || !new_token)
		return (1);
	if (!*head)
	{
		*head = new_token;
		return (0);
	}
	temp = *head;
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = new_token;
	new_token->prev = temp;
	return (0);
}

void	free_tokens(t_token **head)
{
	t_token	*c;
	t_token	*next;

	if (!head || !*head)
		return ;
	c = *head;
	while (c != NULL)
	{
		next = c->next;
		if (c->str)
			free(c->str);
		free(c);
		c = next;
	}
	*head = NULL;
}

int	is_f_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}
