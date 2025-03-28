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

int	handle_word(char *input, int i, t_token **head, int *id)
{
	int	err;

	err = 0;
	while (input[i] && !isspace(input[i]) && !is_f_operator(input[i]) \
	&& input[i] != '\'' && input[i] != '"')
	{
		err = token_back(head, c_token(NULL, input[i], (*id)++, O_WORD));
		if (err)
			return (-1);
		i++;
	}
	return (i - 1);
}

int	handle_quotes(char *input, int start, t_token **head, int *id)
{
	char	quote_type;
	int		i;
	int		err;

	i = start + 1;
	quote_type = input[start];
	err = 0;
	err = token_back(head, c_token(NULL, input[start], (*id)++, O_WORD));
	if (err)
		return (-1);
	while (input[i] && input[i] != quote_type)
	{
		err = token_back(head, c_token(NULL, input[i], (*id)++, O_WORD));
		if (err)
			return (-1);
		i++;
	}
	if (input[i] == quote_type)
		err = token_back(head, c_token(NULL, input[i], (*id)++, O_WORD));
	if (err)
		return (-1);
	return (i);
}

int	handle_operator(char *input, int i, t_token **head, int *id)
{
	t_operators	op;
	char		*temp;
	int			err;

	op = id_op(input[i], input[i + 1]);
	if (op == O_OR || op == O_AND || op == O_DLESS || op == O_DGREAT)
	{
		temp = ft_substr(input, i, 2);
		err = token_back(head, c_token(temp, (char)input[i], (*id)++, op));
		free (temp);
	}
	else
		err = token_back(head, c_token(NULL, (char)input[i], (*id)++, op));
	if (op == O_OR || op == O_AND || op == O_DLESS || op == O_DGREAT)
		i++;
	if (err)
		return (-1);
	return (i);
}

t_token	*tokenize_input(char *ip, int id, int i)
{
	t_token	*head;

	head = NULL;
	while (ip[i])
	{
		if (ft_isspace(ip[i]))
		{
			if (token_back(&head, c_token(NULL, (char)ip[i], (id)++, O_SPACE)))
				return (NULL);
			i++;
			continue ;
		}
		if (is_f_operator(ip[i]))
			i = handle_operator(ip, i, &head, &id);
		else if (ip[i] == '\'' || ip[i] == '\"')
			i = handle_quotes(ip, i, &head, &id);
		else
			i = handle_word(ip, i, &head, &id);
		if (i < 0)
			return (NULL);
		if (ip[i] != '\0')
			i++;
	}
	return (head);
}
