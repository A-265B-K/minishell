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

#include "../inc/minishell.h"


void	tokenize(t_program *program)
{
	// tokenize should create an array of tokens that are formatted according to quoting rules
	// envp between 2 " ", will be shell expanded, but not between ' '

	char	*input;






	input = program->user_input;
	// cmds_amount = ft_strlen(split_array);
	// current_node = program->tokens;
	program->tokens = minishell_split(program->user_input);
	// give tokens their types

}

// void	link_nodes()
// {
// 	// if current_node
// 	// 	current_node->next = new_node
// 	// 	new_node->prev = current_node
// 	// current_node = new_node
// }


t_token	*minishell_split(char *str)
{
	size_t	start;
	size_t	end;
	t_token	*head_node;
	t_token	*current_node;
	char	*command;


	start = 0;

	head_node = malloc(sizeof(t_token*));
	current_node = malloc(sizeof(t_token*));

	start = 0;
	end = start;
	while (str[end] && !is_operator_token(&str[end]))
		end++;

	head_node->command = ft_strndup(&str[start], end - start);
	start = end;
	current_node = head_node;

	while (str[start])
	{
		while (str[start] && is_operator_token(&str[start]))
			start++;
		end = start;
		while (str[end] && !is_operator_token(&str[end]))
			end++;
		command = strndup(&str[start], end - start);
		current_node->next = new_node(command);
		free(command);
		start = end;
		current_node->next->previous = current_node;
		current_node = current_node->next;

	}
	return (head_node);
}
