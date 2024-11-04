/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebayat <ebayat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:42:31 by ebayat            #+#    #+#             */
/*   Updated: 2024/08/02 15:40:26 by ebayat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/* fix, token point is 0 pointer*/

#define TOKEN_SIZE 64

void	split_input(t_token *tokens, char *user_input)
{
	char *current_token = malloc(TOKEN_SIZE);
	if (!current_token)
		return ;
	ft_bzero(current_token, TOKEN_SIZE);
	
	int current_length = 0;
	int token_size = TOKEN_SIZE;
	bool single_quote = false;
	bool double_quote = false;
	for (int i = 0; user_input[i] != '\0'; i++)
	{
		char c = user_input[i];
		if (c == ' ' && !single_quote && !double_quote)
		{
			if (current_length > 0)
			{
				add_to_back(tokens, current_token);
				ft_bzero(current_token, token_size);
				current_length = 0;
			}
		}
		else if (c == '\'')
		{
			if (single_quote && current_length > 0)
			{
				printf("something got added\n");
				add_to_back(tokens, current_token);
				ft_bzero(current_token, token_size);
				current_length = 0;
				single_quote = false;
				double_quote = false;
			}
			else
				single_quote = true;
		}
		else if (c == '\"')
		{
			if (double_quote && current_length > 0)
			{
				printf("something got added\n");
				add_to_back(tokens, current_token);
				ft_bzero(current_token, token_size);
				current_length = 0;
				single_quote = false;
				double_quote = false;
			}
			else
				double_quote = true;
		}
		else
			current_token[current_length++] = c;
		printf("Current token: %s\n", current_token);
	}
	if (current_token[0])
		add_to_back(tokens, current_token);
	free(current_token);
}

void	tokenize(t_token *tokens)
{
	printf(">>>> TOKENIZED\n");
	split_input(tokens->next, tokens->data);
//	add_to_back(tokens, "Hello World");



}


// void	link_nodes()
// {
// 	// if current_node
// 	// 	current_node->next = new_node
// 	// 	new_node->prev = current_node
// 	// current_node = new_node
// }


// t_token	*minishell_split(char *str)
// {
// 	size_t	start;
// 	size_t	end;
// 	t_token	*head_node;
// 	t_token	*current_node;
// 	char	*command;


// 	start = 0;

// 	head_node = malloc(sizeof(t_token*));
// 	current_node = malloc(sizeof(t_token*));

// 	start = 0;
// 	end = start;
// 	while (str[end] && !is_operator_token(&str[end]))
// 		end++;

// 	head_node->command = ft_strndup(&str[start], end - start);
// 	start = end;
// 	current_node = head_node;

// 	while (str[start])
// 	{
// 		while (str[start] && is_operator_token(&str[start]))
// 			start++;
// 		end = start;
// 		while (str[end] && !is_operator_token(&str[end]))
// 			end++;
// 		command = strndup(&str[start], end - start);
// 		current_node->next = new_node(command);
// 		free(command);
// 		start = end;
// 		current_node->next->previous = current_node;
// 		current_node = current_node->next;

// 	}
// 	return (head_node);
// }

