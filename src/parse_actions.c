/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:36:44 by marvin            #+#    #+#             */
/*   Updated: 2025/03/19 17:36:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_redir(t_commands *command, t_token *current, t_shell *shell)
{
	int	result;

	if (current->token == O_DLESS)
	{
		result = handle_heredoc(command, current->next, shell);
		if (result)
			return (error_handler("Heredoc error", 1));
	}
	else if (current->token == O_LESS || current->token == O_GREAT \
			|| current->token == O_DGREAT)
	{
		command->redirection = realloc(command->redirection, \
			sizeof(char *) * (command->red_count + 2));
		if (!command->redirection)
			return (error_handler("Malloc error @ parse_redir", 1));
		command->redirection[command->red_count] = \
		ft_strjoin(current->str, current->next->str);
		command->redirection[command->red_count + 1] = NULL;
		command->red_count++;
	}
	return (0);
}

int	identify_builtin(t_commands *command, t_token *current)
{
	if (ft_strncmp(current->str, "echo", 4) == 0 \
	|| ft_strncmp(current->str, "cd", 2) == 0 \
	|| ft_strncmp(current->str, "pwd", 3) == 0 \
	|| ft_strncmp(current->str, "env", 3) == 0)
	{
		if (!command->builtin)
		{
			command->builtin = ft_strdup(current->str);
			return (1);
		}
	}
	if (ft_strncmp(current->str, "export", 6) == 0 \
	|| ft_strncmp(current->str, "unset", 5) == 0 \
	|| ft_strncmp(current->str, "exit", 4) == 0)
	{
		if (!command->builtin)
		{
			command->builtin = ft_strdup(current->str);
			return (1);
		}
	}
	return (0);
}

int	parse_pipe(t_commands **com, t_commands **c_com, int node_count)
{
	add_command_to_list(com, *c_com);
	node_count++;
	*c_com = create_command_node(node_count);
	return (node_count);
}

int	parse_builtin(t_token *c_tok, t_commands *c_com, int arg_count)
{
	if (c_tok->token == O_G_WORD)
	{
		if (!identify_builtin(c_com, c_tok))
		{
			c_com->str = realloc(c_com->str, sizeof(char *) * (arg_count + 2));
			if (!c_com->str)
				return (error_handler("Malloc error @ parse_builtin", -1));
			c_com->str[arg_count] = ft_strdup(c_tok->str);
			c_com->str[arg_count + 1] = NULL;
			arg_count++;
		}
	}
	return (arg_count);
}

int	p_redir(t_commands *c_com, t_token **c_tok, int c, t_shell *shell)
{
	int	result;

	if ((*c_tok)->token == O_LESS || (*c_tok)->token == O_GREAT || \
		(*c_tok)->token == O_DLESS || (*c_tok)->token == O_DGREAT)
	{
		result = parse_redir(c_com, *c_tok, shell);
		if (result)
			return (-1);
		*c_tok = (*c_tok)->next->next;
	}
	else if ((*c_tok)->token == O_G_WORD)
	{
		c = parse_builtin(*c_tok, c_com, c);
		if (c < 0)
			return (-1);
		*c_tok = (*c_tok)->next;
	}
	return (c);
}
