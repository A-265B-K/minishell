/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:31:03 by marvin            #+#    #+#             */
/*   Updated: 2025/03/27 21:54:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		free(tmp);
	}
}

char	*rm_quotes(char *str)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	res = malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}

int	ft_isvalid(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' \
		|| c == ' ' || c == '\'' || c == '\"' || c == '\0' || c == '\n')
		return (1);
	return (0);
}
