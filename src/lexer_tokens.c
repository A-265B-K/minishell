/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:50:43 by marvin            #+#    #+#             */
/*   Updated: 2025/03/19 17:50:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_operators	id_op(char c, char c_plus)
{
	if (c == '|' && c_plus == '|')
		return (O_OR);
	if (c == '&' && c_plus == '&')
		return (O_AND);
	if (c == '<' && c_plus == '<')
		return (O_DLESS);
	if (c == '>' && c_plus == '>')
		return (O_DGREAT);
	if (c == '|')
		return (O_PIPE);
	if (c == '<')
		return (O_LESS);
	if (c == '>')
		return (O_GREAT);
	return (-1);
}

int	handle_word(const char *input, int i, t_token **head, int *id)
{
	while (input[i] && !isspace(input[i]) && !is_f_operator(input[i]) \
	&& input[i] != '\'' && input[i] != '"')
	{
		token_back(head, c_token(NULL, input[i], (*id)++, O_WORD));
		i++;
	}
	return (i - 1);
}

int	handle_quotes(const char *input, int start, t_token **head, int *id)
{
	char	quote_type;
	int		i;

	i = start + 1;
	quote_type = input[start];
	token_back(head, c_token(NULL, input[start], (*id)++, O_WORD));
	while (input[i] && input[i] != quote_type)
	{
		token_back(head, c_token(NULL, input[i], (*id)++, O_WORD));
		i++;
	}
	if (input[i] == quote_type)
		token_back(head, c_token(NULL, input[i], (*id)++, O_WORD));
	return (i);
}

int	handle_operator(const char *input, int i, t_token **head, int *id)
{
	t_operators	op;
	char		*temp;

	op = id_op(input[i], input[i + 1]);
	if (op == O_OR || op == O_AND || op == O_DLESS || op == O_DGREAT)
	{
		temp = ft_substr(input, i, 2);
		token_back(head, c_token(temp, (char)input[i], (*id)++, op));
		free (temp);
	}
	else
		token_back(head, c_token(NULL, (char)input[i], (*id)++, op));
	if (op == O_OR || op == O_AND || op == O_DLESS || op == O_DGREAT)
		i++;
	return (i);
}

t_token	*tokenize_input(const char *input)
{
	t_token	*head;
	int		id;
	int		i;

	head = NULL;
	id = 0;
	i = 0;
	while (input[i])
	{
		if (isspace(input[i]))
		{
			token_back(&head, c_token(NULL, (char)input[i], (id)++, O_SPACE));
			i++;
			continue ;
		}
		if (is_f_operator(input[i]))
			i = handle_operator(input, i, &head, &id);
		else if (input[i] == '\'' || input[i] == '\"')
			i = handle_quotes(input, i, &head, &id);
		else
			i = handle_word(input, i, &head, &id);
        if (input[i] != '\0')
		    i++;
	}
	return (head);
}
