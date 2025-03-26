/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:41:34 by marvin            #+#    #+#             */
/*   Updated: 2025/03/19 17:41:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_parser(t_commands *commands)
{
	// int	command_index;

	// command_index = 1;
	while (commands)
	{
		// printf("Command %d:\n", command_index++);
        printf("command id = [%d]\n", commands->id);
		if (commands->str)
		{
			printf("  Arguments: ");
			for (int i = 0; commands->str[i] != NULL; i++)
			{
				printf("[%s] ", commands->str[i]);
			}
            printf("\n");
		}
		else
			printf("  Arguments: None\n");
		if (commands->builtin)
			printf("  Builtin: %s\n", commands->builtin);
		else
			printf("  Builtin: None\n");
		if (commands->redirection)
		{
			printf("  redirections: ");
			for (int j = 0; commands->redirection[j] != NULL; j++)
			{
				printf("[%s] ", commands->redirection[j]);
			}
            printf("\n");
		}
		else
			printf("  Redirection: None\n");
		commands = commands->next;
	}
}

void	print_grouped(t_token *head)
{
	t_token	*temp;

	temp = head;
	printf("GROUPED!\n");
	while (temp)
	{
		printf("str: %s, ID: %d, Token: %d\n", temp->str, temp->id, temp->token);
		temp = temp->next;
	}
}

void	print_tokens(t_token *head)
{
	t_token	*temp;

	temp = head;
	while (temp)
	{
		printf("Char: %c, ID: %d, Token: %d\n", temp->c, temp->id, temp->token);
		temp = temp->next;
	}
}

void    print_array(char **str)
{
    int i;

    i = 0;
    while (str[i])
    {
        printf("%s\n", str[i]);
        i++;
    }
}
