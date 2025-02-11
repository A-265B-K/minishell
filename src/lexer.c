/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahornstr <ahornstr@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/02 15:06:43 by ahornstr      #+#    #+#                 */
/*   Updated: 2025/02/11 17:25:45 by wdpk          ########   odam.nl         */
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
	// if (c == '$')
	// 	return (O_ENVV);
    return (-1);
}

int handle_word(const char *input, int i, t_token **head, int *id)
{
    while (input[i] && !isspace(input[i]) && !is_operator(input[i]) && input[i] != '\'' && input[i] != '"')
	{
        token_add_back(head, create_token(NULL, input[i], (*id)++, O_WORD));
        i++;
    }
    return (i - 1);
}

// this doesnt work anymore
int	handle_quotes(const char *input, int start, t_token **head, int *id)
{
    char quote_type;
	int	i;
	
	i = start + 1;
	quote_type = input[start];
    token_add_back(head, create_token(NULL, input[start], (*id)++, O_WORD));
    while (input[i] && input[i] != quote_type) {
        token_add_back(head, create_token(NULL, input[i], (*id)++, O_WORD));
        i++;
    }
    if (input[i] == quote_type)
        token_add_back(head, create_token(NULL, input[i], (*id)++, O_WORD));
    return (i);
}

int	handle_operator(const char *input, int i, t_token **head, int *id)
{
    t_operators	op;
    char		*temp;

    temp = mem_add(1, 3);
	op = identify_operator(input[i], input[i + 1]);
    if (op == O_OR || op == O_AND || op == O_DLESS || op == O_DGREAT)
        temp = ft_strdup(ft_substr(input, i, 2));
    token_add_back(head, create_token(temp, (char)input[i], (*id)++, op));
    if (op == O_OR || op == O_AND || op == O_DLESS || op == O_DGREAT)
        i++;
    free (temp);
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
        {
            token_add_back(&head, create_token(NULL, (char)input[i], (id)++, O_SPACE));
            i++;
            continue;
        }
        if (is_operator(input[i]))
            i = handle_operator(input, i, &head, &id);
		else if (input[i] == '\'' || input[i] == '"')
        	i = handle_quotes(input, i, &head, &id);
		else
			i = handle_word(input, i, &head, &id);
		i++;
    }
    return (head);
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

void init_lexer_tools(t_lexer_tools *tools)
{
    tools->buffer = NULL;
    tools->id = 0;
    tools->mem_size = 0;
    tools->token_len = 0;
    tools->quote_flag = 0;
    tools->quote_type = '\0';
}

void finalize_token(t_token **lexer_grouped, t_lexer_tools *tools, t_operators type)
{
    if (tools->token_len > 0)
    {
		if (!tools->buffer)
			tools->buffer = mem_add(1, 1);
		tools->buffer[tools->token_len] = '\0';
        token_add_back(lexer_grouped, create_token(tools->buffer, 0, tools->id++, type));
        tools->token_len = 0;
    }
}

void handle_operator_token(t_token **lexer_grouped, t_token **current, t_lexer_tools *tools)
{
    char    *temp;

    temp = NULL;
    finalize_token(lexer_grouped, tools, O_G_WORD);
    if ((*current)->str && ((*current)->token == O_OR || (*current)->token == O_AND || (*current)->token == O_DGREAT || (*current)->token == O_DLESS))
    {
        temp = ft_strdup((*current)->str);
        if (!temp)
            error("malloc error handle operator token\n");
    }
    else
    {
        temp = mem_add(1, 2);
        temp[0] = (*current)->c;
    }
    token_add_back(lexer_grouped, create_token(temp, 0, tools->id++, identify_operator(temp[0], temp[1])));
    free (temp);
}

void append_to_buffer(t_lexer_tools *tools, char c)
{
    while (tools->token_len + 1 >= tools->mem_size)
	{
		if (tools->mem_size == 0)
			tools->mem_size += 1;
		else
        	tools->mem_size *=2;
	}
	if (tools->buffer)
	{
        tools->buffer = realloc(tools->buffer, tools->mem_size);
	}
	else
		tools->buffer = mem_add(tools->mem_size, sizeof(char));
    if (!tools->buffer)
		return;
	tools->buffer[tools->token_len++] = c;
}

int group_quotes(t_token **current, char c)
{
    if (((*current)->c != c))
        return (1);
    return (0);
}

int	quote_group(t_token **current, t_lexer_tools *tools, t_token **lexer_grouped)
{
	tools->quote_flag = 1;
    tools->quote_type = (*current)->c;
    append_to_buffer(tools, (*current)->c);
    (*current) = (*current)->next;
    while ((*current) && group_quotes(&(*current), tools->quote_type))
    {
        append_to_buffer(tools, (*current)->c);
        (*current) = (*current)->next;
    }
    if((*current) && ((*current)->c == tools->quote_type || (*current)->c == tools->quote_type))
    {
    	tools->quote_flag = 0;
        append_to_buffer(tools, (*current)->c);
        finalize_token(lexer_grouped, tools, O_G_WORD);
        (*current) = (*current)->next;
        return (0);
    }
	return (1);
}

t_token *group_tokens(t_token *lexer_input)
{
    t_token *lexer_grouped = NULL;
    t_token *current = lexer_input;
    t_lexer_tools tools;

    init_lexer_tools(&tools);
    while (current)
    {
        if(current->c == '\'' || current->c == '\"')
        {
            if (!quote_group(&current, &tools, &lexer_grouped))
				continue;
        }
        if (current && isspace(current->c))
            finalize_token(&lexer_grouped, &tools, O_G_WORD);
        else if (current && is_operator(current->c))
            handle_operator_token(&lexer_grouped, &current, &tools);
        else if (current)
            append_to_buffer(&tools, current->c);
		current = current->next;
    }
    finalize_token(&lexer_grouped, &tools, O_G_WORD);
    free(tools.buffer);
    return (lexer_grouped);
}


void print_grouped(t_token *head)
{
    t_token *temp;
	temp = head;
    printf("GROUPED!\n");
    while (temp)
	{
        printf("str: %s, ID: %d, Token: %d\n", temp->str, temp->id, temp->token);
        temp = temp->next;
    }
}

int	lexer(t_shell *shell)
{
    if(!unclosed_quotes(shell->input))
	{
		(error("Unclosed quotes\n"));
		return (0);
	}
	shell->tokenized = tokenize_input(shell->input);
	// print_tokens(shell->tokenized);
    shell->lexer_grouped = group_tokens(shell->tokenized);
   // print_grouped(shell->lexer_grouped);
	return (1);
}