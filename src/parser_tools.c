/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:31:03 by marvin            #+#    #+#             */
/*   Updated: 2025/03/22 00:54:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    init_reds(t_redirects *reds)
{
    reds->err_fd = 0;
    reds->in_fd = 0;
    reds->out_fd = 0;
    reds->sstderr = NULL;
    reds->sstdin = NULL;
    reds->sstdout = NULL;
}

t_commands	*create_command_node(int count)
{
	t_commands	*new_command;

	new_command = malloc(sizeof(t_commands));
	if (!new_command)
		return (NULL);
	new_command->id = count;
    new_command->red_count = 0;
	new_command->str = NULL;
	new_command->builtin = NULL;
	new_command->tokenized = NULL;
	new_command->redirection = NULL;
    new_command->hd_name = NULL;
	new_command->next = NULL;
	new_command->prev = NULL;
	return (new_command);
}

void	add_command_to_list(t_commands **commands, t_commands *new_command)
{
	t_commands	*last;

	last = NULL;
	if (*commands == NULL)
		*commands = new_command;
	else
	{
		last = *commands;
		while (last->next)
			last = last->next;
		last->next = new_command;
		new_command->prev = last;
	}
}

void    free_reds(t_redirects *reds)
{
    if (reds->sstderr)
        free (reds->sstderr);
    if (reds->sstdin)
        free (reds->sstdin);
    if (reds->sstdout)
        free (reds->sstdout);
    free (reds);
}

void	free_command_list(t_commands *commands)
{
	t_commands	*tmp;

	while (commands)
	{
		tmp = commands;
		commands = commands->next;
        if (tmp->str)
		    free_double(tmp->str);
		if (tmp->builtin)
			free(tmp->builtin);
		if (tmp->tokenized)
			free_tokens(&tmp->tokenized);
		if (tmp->redirection)
			free_double(tmp->redirection);
        if (tmp->hd_name)
            free(tmp->hd_name);
        // if (tmp->redirects)
        //     free_reds(tmp->redirects);
		free(tmp);
	}
}

void	free_command_node(t_commands *command)
{
	if (!command)
		return ;
	while (command && command->id != 0)
		command = command->prev;
	while (command && command->next)
	{
		if (command->str)
            free_double(command->str);
		if (command->redirection)
			free_double(command->redirection);
		if (command->builtin)
			free(command->builtin);
        if (command->tokenized)
            free_tokens(&command->tokenized);
        if (command->hd_name)
            free(command->hd_name);
		command = command->next;
	}
	free(command);
}

int	var_len(const char *input, int *i)
{
	int	start;
	int	len;

	start = *i + 1;
	while (ft_isalnum(input[start]) || input[start] == '_')
		start++;
	len = start - (*i + 1);
	if (len <= 0)
		return (0);
	return (len);
}
