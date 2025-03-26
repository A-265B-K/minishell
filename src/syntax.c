/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:01:11 by marvin            #+#    #+#             */
/*   Updated: 2025/03/26 01:37:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	if (!c)
		return (0);
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	else if (c == '\v' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int ft_isquote(char c)
{
    if (c == '\'' || c == '\"')
        return (1);
    return (0);
}

int	syntax_check(t_shell *shell)
{
	if (operator_placement(shell))
    {
        shell->exitcode = 2;
		return (1);
    }
	return (0);
}

int valid_combo(char *str, int i)
{
    char    *temp;

    temp = ft_substr(str, i, 2);
    if (!temp)
        return (0);
    if (ft_strncmp(temp, "<<", 2) || ft_strncmp(temp, ">>", 2) \
        || ft_strncmp(temp, "||", 2))
    {
        free (temp);
        return (1);
    }
    free (temp);
    return (0);
}

int increment_quote(char *str, int i)
{
    int s;
    int d;
    
    s = 0;
    d = 0;
    while (str[i])
    {
        if (str[i] == '\"' && d == 0 && s == 0)
            d = 1;
        else if (str[i] == '\"' && d == 1)
        {
            d = 0;
            return (i);
        }
        if (str[i] == '\'' && s == 0 && d == 0)
            s = 1;
        else if (str[i] == '\'' && s == 1)
        {
            s = 0;
            return (i);
        }
        i++;
    }
    return (i - 1);
}

int	combo_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isquote(str[i]))
            i = increment_quote(str, i);
		if (is_f_operator(str[i]))
		{
			if (is_f_operator(str[i + 1]))
			{
				if (valid_combo(str, i))
					return (0);
			}
		}
		i++;
	}
	return (1);
}

int	operator_check(char *str)
{
	int	i;

	i = 0;
	if (!combo_check(str))
		return (0);
	while (str[i])
	{
        if (ft_isquote(str[i]))
		{
            i = increment_quote(str, i);
			if (str[i + 1] == '\0')
				break ;
		}
		if (is_f_operator(str[i]))
		{
			while (ft_isspace(str[i]))
			{
				i++;
				if (is_f_operator(str[i]))
                	return (0);
			}
		}
		i++;
	}
	return (1);
}

int	unclosed_quotes(const char *input)
{
	char	open_quote;
	int		i;

	i = 0;
	open_quote = '\0';
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			if (open_quote == '\0')
				open_quote = input[i];
			else if (open_quote == input[i])
				open_quote = '\0';
		}
		i++;
	}
	if (open_quote != '\0')
		return (0);
	return (1);
}

int	operator_placement(t_shell *shell)
{
	t_token	*temp;

	if (shell->tokenized)
		temp = shell->tokenized;
	else
		return (0);
	while (temp && temp->id != 0)
	{
		temp = temp->prev;
	}
	while (temp)
	{
		if (is_f_operator(temp->c))
		{
			if ((is_f_operator(temp->c) && !temp->next) || \
			temp->id == 0 || \
			!operator_check(shell->input))
			{
				fprintf(stderr, " syntax error near unexpected token `%c'\n", temp->c);
				return (1);
			}
		}
		temp = temp->next;
	}
	return (0);
}
