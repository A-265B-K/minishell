/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:12:03 by marvin            #+#    #+#             */
/*   Updated: 2025/03/28 03:00:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_commands	*parse_tokens(t_token *lex, int ac, int nc, t_shell *shell)
{
	t_commands	*commands;
	t_commands	*c_com;
	t_token		*c_tok;

	commands = NULL;
	c_com = create_command_node(0);
	c_tok = lex;
	while (c_tok)
	{
		if (c_tok->token == O_PIPE)
		{
			nc = parse_pipe(&commands, &c_com, nc);
			c_tok = c_tok->next;
			ac = 0;
		}
		ac = p_redir(c_com, &c_tok, ac, shell);
		if (ac < 0)
			return (free_command_list(c_com), NULL);
	}
	if (c_com->str || c_com->redirection || c_com->builtin)
		add_command_to_list(&commands, c_com);
	else
		free_command_list(c_com);
	return (commands);
}

int	quotes_in_commands(t_commands *cmd, t_shell *shell, char *temp)
{
	int		i;

	while (cmd)
	{
		if (cmd->builtin)
		{
			temp = expand_quotes(cmd->builtin, shell);
			if (!temp)
				return (free(cmd->builtin), 1);
			free(cmd->builtin);
			cmd->builtin = temp;
		}
		i = 0;
		while (cmd->str && cmd->str[i])
		{
			temp = expand_quotes(cmd->str[i], shell);
			if (!temp)
				return (free(cmd->str[i]), 1);
			free(cmd->str[i]);
			cmd->str[i] = temp;
			i++;
		}
		cmd = cmd->next;
	}
	return (0);
}

char	*expand_quotes(char *s, t_shell *shell)
{
	t_q		q;
	char	*result;

	init_q(&q);
	result = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!result)
		return (NULL);
	result[0] = '\0';
	while (s[q.i])
	{
		toggle_quotes(s[q.i], &q);
		if (s[q.i] == '$' && !q.in_s && !ft_isvalid(s[q.i + 1]))
		{
			if (handle_exp(s, &result, shell, &q))
			{
				free(result);
				return (NULL);
			}
		}
		else if (!(s[q.i] == '\'' && !q.in_d) && !(s[q.i] == '"' && !q.in_s))
			handle_regular_char(s, &result, &q);
		q.i++;
	}
	result[q.j] = '\0';
	return (result);
}

int	quotes_in_redirects(t_commands *cmd)
{
	int		i;
	char	*temp;

	temp = NULL;
	while (cmd)
	{
		i = 0;
		while (cmd->redirection && cmd->redirection[i])
		{
			temp = rm_quotes(cmd->redirection[i]);
			if (!temp)
				return (free(cmd->redirection), 1);
			free(cmd->redirection[i]);
			cmd->redirection[i] = temp;
			i++;
		}
		cmd = cmd->next;
	}
	return (0);
}

int	parser(t_shell	*shell)
{
	if (syntax_check(shell))
		return (2);
	shell->com_struct = parse_tokens(shell->lex, 0, 0, shell);
	if (!shell->com_struct)
		return (1);
	if (quotes_in_commands(shell->com_struct, shell, NULL))
		return (1);
	if (!shell->com_struct)
		return (1);
	if (quotes_in_redirects(shell->com_struct))
		return (1);
	return (0);
}
