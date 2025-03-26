/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:39:47 by marvin            #+#    #+#             */
/*   Updated: 2025/03/19 17:39:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_isvalid(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ' || c == '\'' || c == '\"' || c == '\0' || c == '\n')
		return (1);
	return (0);
}

char	*expand_env_var(const char *var, t_shell *shell)
{
	char	*value;
	char	*temp;

	value = ft_getenv(var, shell);
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

// void	toggle_quotes(char c, int *in_single, int *in_double)
// {
// 	if (c == '\'' && !(*in_double))
// 		*in_single = !(*in_single);
// 	else if (c == '"' && !(*in_single))
// 		*in_double = !(*in_double);
// }

// int	handle_exitcode(char **result, int *j, int *i, t_shell *shell)
// {
// 	int		new_size;
// 	int		len;

// 	len = ft_strlen(ft_itoa(shell->exitcode));
// 	new_size = ft_strlen(*result) + len + 1;
// 	*result = realloc(*result, new_size);
// 	if (!*result)
// 		return (1);
// 	memcpy(&(*result)[*j], ft_itoa(shell->exitcode), len);
// 	*j += len;
// 	*i += 1;
// 	return (0);
// }

