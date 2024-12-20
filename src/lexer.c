/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahornstr <ahornstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:06:43 by ahornstr          #+#    #+#             */
/*   Updated: 2024/12/20 14:21:58 by ahornstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_operators	identify_operator(char c, char c_plus)
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
    return -1;
}

int	is_operator(char c)
{
	if (c == '|' || c == ';' || c == '<' || c == '>' || c == '&')
		return (1);
	return (0);
}

int handle_word(const char *input, int i, t_token **head, int *id)
{
    while (input[i] && !isspace(input[i]) && !is_operator(input[i]) && input[i] != '\'' && input[i] != '"')
	{
        token_add_back(head, create_token(input[i], (*id)++, O_WORD));
        i++;
    }
    return (i - 1);
}

int	handle_quotes(const char *input, int start, t_token **head, int *id)
{
    char quote_type;
	int	i;
	
	i = start + 1;
	quote_type = input[start];
    token_add_back(head, create_token(input[start], (*id)++, O_WORD));
    while (input[i] && input[i] != quote_type) {
        token_add_back(head, create_token(input[i], (*id)++, O_WORD));
        i++;
    }
    if (input[i] == quote_type)
        token_add_back(head, create_token(input[i], (*id)++, O_WORD));
    return (i);
}

int	handle_operator(const char *input, int i, t_token **head, int *id)
{
    t_operators op;
	op = identify_operator(input[i], input[i + 1]);
    token_add_back(head, create_token((char)input[i], (*id)++, op));
    if (op == O_OR || op == O_AND || op == O_DLESS || op == O_DGREAT)
        i++;
    return (i);
}

t_token *tokenize_input(const char *input)
{
    t_token *head = NULL;
    int id = 0;
	int	i;
	
	i = 0;
    while (input[i])
	{
        if (isspace(input[i]))
			i++;
        if (is_operator(input[i]))
            i = handle_operator(input, i, &head, &id);
		else if (input[i] == '\'' || input[i] == '"')
        	i = handle_quotes(input, i, &head, &id);
		else
			i = handle_word(input, i, &head, &id);
		i++;
    }
    return head;
}

void print_tokens(t_token *head)
{
    t_token *temp;
	temp = head;
    while (temp)
	{
        printf("Char: %c, ID: %d, Token: %d\n", temp->c, temp->id, temp->token);
        temp = temp->next;
    }
}

void	lexer(t_shell *shell)
{
	shell->tokenized = tokenize_input(shell->input);
	print_tokens(shell->tokenized);
	// free_tokens(shell->tokenized);
}