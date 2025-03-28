/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:01:11 by marvin            #+#    #+#             */
/*   Updated: 2025/03/28 02:28:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_check(t_shell *shell)
{
	if (operator_placement(shell))
	{
		shell->exitcode = 2;
		return (1);
	}
	return (0);
}

int	increment_quote(char *str, int i)
{
	int	s;
	int	d;

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
				if (!valid_combo(str, i))
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

int	operator_placement(t_shell *shell)
{
	t_token	*temp;

	if (shell->tokenized)
		temp = shell->tokenized;
	else
		return (0);
	while (temp && temp->id != 0)
		temp = temp->prev;
	while (temp)
	{
		if (is_f_operator(temp->c))
		{
			if ((is_f_operator(temp->c) && !temp->next) || \
			check_hd(shell->input) || \
			!operator_check(shell->input))
			{
				ft_putstr_fd(" syntax error near unexpected token `", 2);
				ft_putchar_fd(temp->c, STDERR_FILENO);
				ft_putstr_fd("'\n", STDERR_FILENO);
				return (1);
			}
		}
		temp = temp->next;
	}
	return (0);
}
