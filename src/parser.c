/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahornstr <ahornstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 12:41:34 by ahornstr          #+#    #+#             */
/*   Updated: 2024/12/20 14:47:28 by ahornstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// try and return errornums in syntax_check

int	operator_placement(t_shell *shell)
{
	// check if this is the correct way to make temp
	t_token	*temp;
	temp = shell->tokenized;
	// make a temporary list and iterate over
	printf("//// temp_test //// \n");
	while (temp->id != 0)
	{
		temp = temp->prev;
	}
	while (temp)
	{
		printf("char_temp: %c,  ID_temp: %d, Tok_temp: %u\n", temp->c, temp->id, temp->token);
		if (is_operator(temp->c))
		{
			if (is_operator(temp->c) && !temp->next)
				error("syntax error near unexpected token\n");
		}
		temp = temp->next;
	}
	return (0);
}

int	syntax_check(t_shell *shell)
{
	// function to check if operators are in valid positions
	if (!operator_placement(shell))
	{
		printf("Operators place correct\n");
	}
	else
		return (42);
	return (0);
}

void	parser(t_shell	*shell)
{
	if(!syntax_check(shell))
	{
		printf("SYNTAX VALID\n");
	}
	free_tokens(shell->tokenized);
}