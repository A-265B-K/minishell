/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 21:48:13 by marvin            #+#    #+#             */
/*   Updated: 2025/03/27 21:48:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*expand_env_var(char *var, t_shell *shell)
{
	char	*value;
	char	*temp;

	value = ft_env_get(var, shell->envp);
	if (!value)
	{
		temp = ft_strdup("");
		free(value);
		return (temp);
	}
	temp = ft_strdup(value);
	free (value);
	return (temp);
}

int	variable_expansion(char *ip, char **result, t_q *q, t_shell *shell)
{
	char	*var_name;
	char	*exp;
	int		len;

	len = var_len(ip, &q->i);
	var_name = malloc(len + 1);
	if (!var_name)
		return (0);
	ft_strlcpy(var_name, &ip[q->i + 1], len + 1);
	exp = expand_env_var(var_name, shell);
	if (exp)
	{
		*result = ft_realloc(*result, \
			q->j, q->j + ft_strlen(exp) + 1 + ft_strlen(ip));
		if (!*result)
			return (free(exp), 0);
		ft_memcpy(&(*result)[q->j], exp, ft_strlen(exp));
		q->j += ft_strlen(exp);
	}
	if (exp)
		free(exp);
	q->i += len;
	return (free(var_name), 1);
}
