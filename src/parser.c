/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:12:03 by marvin            #+#    #+#             */
/*   Updated: 2025/03/26 01:34:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_commands	*parse_tokens(t_token *lex, int arg_count, int node_count, t_shell *shell)
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
			node_count = parse_pipe(&commands, &c_com, node_count);
			c_tok = c_tok->next;
			arg_count = 0;
		}
		arg_count = parse_help(c_com, &c_tok, arg_count, shell);
		if (arg_count < 0)
			return (free_command_node(c_com), NULL);
	}
	if (c_com->str || c_com->redirection || c_com->builtin)
		add_command_to_list(&commands, c_com);
	else
		free_command_node(c_com);
	return (commands);
}

// int	variable_expansion(const char *input, int *i, char **result, int *j)
// {
// 	char	*var_name;
// 	char	*expand;
// 	int		len;

// 	expand = NULL;
// 	len = var_len(input, i);
// 	var_name = malloc(len + 1);
// 	if (!var_name)
// 		return (0);
// 	ft_strlcpy(var_name, &input[*i + 1], len + 1);
// 	expand = expand_env_var(var_name);
// 	free(var_name);
// 	if (expand)
// 	{
// 		*result = realloc(*result, ft_strlen(*result) + ft_strlen(expand) + 1);
// 		if (!*result)
// 			return (free(expand), 0);
// 		memcpy(&(*result)[*j], expand, ft_strlen(expand));
// 		*j += ft_strlen(expand);
// 	}
// 	if (expand)
// 		free (expand);
// 	*i += len;
// 	return (1);
// }

// char	*remove_quotes(const char *input, t_shell *shell, int in_s, int in_d)
// {
// 	int		i;
// 	int		j;
// 	char	*result;

// 	i = 0;
// 	j = 0;
// 	result = malloc(sizeof(char) * (ft_strlen(input) + 1));
// 	if (!result)
// 		return (NULL);
// 	while (input[i])
// 	{
// 		toggle_quotes(input[i], &in_s, &in_d);
// 		if (input[i] == '$' && !in_s && !ft_isvalid(input[i + 1]))
// 		{
// 			if (input[i + 1] == '?')
// 				if (handle_exitcode(&result, &j, &i, shell))
// 					return (NULL);
// 			if (input[i] == '$')
// 				variable_expansion(input, &i, &result, &j);
// 		}
// 		else if (!(input[i] == '\'' && !in_d) && !(input[i] == '"' && !in_s))
// 			result[j++] = input[i];
// 		i++;
// 	}
// 	result[j] = '\0';
// 	return (result);
// }






void	quotes_in_commands(t_commands *cmd, t_shell *shell)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (cmd)
	{
		if (cmd->builtin)
		{
			temp = remove_quotes(cmd->builtin, shell);
			free(cmd->builtin);
			cmd->builtin = temp;
		}
		i = 0;
		while (cmd->str && cmd->str[i])
		{
			temp = remove_quotes(cmd->str[i], shell);
			free(cmd->str[i]);
			cmd->str[i] = temp;
			i++;
		}
		cmd = cmd->next;
	}
}

int handle_exitcode(char **result, t_q *q, t_shell *shell)
{
	int new_size;
	int len;
	char *exitcode_str;

	exitcode_str = ft_itoa(shell->exitcode);
	if (!exitcode_str)
		return (1);
	len = ft_strlen(exitcode_str);
	new_size = q->j + len + 1;
	*result = realloc(*result, new_size);
	if (!*result)
	{
		free(exitcode_str);
		return (1);
	}
	memcpy(&(*result)[q->j], exitcode_str, len);
	q->j += len;
	q->i += 1;
	free(exitcode_str);
	return (0);
}

void toggle_quotes(char c, t_q *q)
{
	if (c == '\'' && !(q->in_d))
		q->in_s = !(q->in_s);
	else if (c == '"' && !(q->in_s))
		q->in_d = !(q->in_d);
}

int variable_expansion(const char *input, char **result, t_q *q, t_shell *shell)
{
	char *var_name;
	char *expand;
	int len;

	len = var_len(input, &q->i);
	var_name = malloc(len + 1);
	if (!var_name)
		return (0);
	ft_strlcpy(var_name, &input[q->i + 1], len + 1);
	expand = expand_env_var(var_name, shell);
	if (expand)
	{
		*result = realloc(*result, q->j + ft_strlen(expand) + 1);
		if (!*result)
		{
			free(expand);
			return (0);
		}
		memcpy(&(*result)[q->j], expand, ft_strlen(expand));
		q->j += ft_strlen(expand);
	}
	if (expand)
		free(expand);
	q->i += len;
	return (free(var_name), 1);
}

void init_q(t_q *q)
{
	q->in_s = 0;
	q->in_d = 0;
	q->i = 0;
	q->j = 0;
}

int handle_dollar_sign(const char *input, char **result, t_shell *shell, t_q *q)
{
	if (input[q->i + 1] == '?')
	{
		if (handle_exitcode(result, q, shell))
			return (1);
	}
	else if (!variable_expansion(input, result, q, shell))
		return (1);
	return (0);
}

void handle_regular_char(const char *input, char **result, t_q *q)
{
	(*result)[q->j] = input[q->i];
	q->j++;
}

char *remove_quotes(const char *input, t_shell *shell)
{
	t_q q;
	char *result;

	init_q(&q);
	result = malloc(sizeof(char) * (ft_strlen(input) + 1));
	if (!result)
		return (NULL);
	result[0] = '\0';
	while (input[q.i])
	{
		toggle_quotes(input[q.i], &q);
		if (input[q.i] == '$' && !q.in_s && !ft_isvalid(input[q.i + 1]))
		{
			if (handle_dollar_sign(input, &result, shell, &q))
			{
				free(result);
				return (NULL);
			}
		}
		else if (!(input[q.i] == '\'' && !q.in_d) && !(input[q.i] == '"' && !q.in_s))
			handle_regular_char(input, &result, &q);
		q.i++;
	}
	result[q.j] = '\0';
	return (result);
}

int	parser(t_shell	*shell)
{
	if (syntax_check(shell))
		return (0);
	shell->com_struct = parse_tokens(shell->lex, 0, 0, shell);
	if (!shell->com_struct)
		return (1);
	// printf("------------------------------------------\nSTEP 1\n");
	// print_parser(shell->com_struct);
	quotes_in_commands(shell->com_struct, shell);
	if (!shell->com_struct)
		return (1);
	// printf("------------------------------------------\nSTEP 2\n");
	// print_parser(shell->com_struct);
	return (0);
	
}
