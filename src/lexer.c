/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahornstr <ahornstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:06:43 by ahornstr          #+#    #+#             */
/*   Updated: 2024/12/10 18:01:34 by ahornstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//

t_operators identify_operator(const char *str) 
{
    if (strcmp(str, "|") == 0)
		return O_PIPE;
    if (strcmp(str, "&&") == 0)
		return O_AND;
    if (strcmp(str, "||") == 0)
		return O_OR;
    if (strcmp(str, "<") == 0)
		return O_LESS;
    if (strcmp(str, "<<") == 0)
		return O_DLESS;
    if (strcmp(str, ">") == 0)
		return O_GREAT;
    if (strcmp(str, ">>") == 0)
		return O_DGREAT;
    return (-1);
}



int	is_operator(char c)
{
	if (c == '|' || c == ';' || c == '<' || c == '>' || c == '&')
		return (1);
	return (0);
}

char	*check_double_operator(t_shell *shell, int i, char *operator)
{
	operator[0] = shell->input[i];
	operator[1] = shell->input[i + 1];
	return (operator);
}

void	tokenizer(t_shell *shell)
{
	int	i;
	char	*operator;
	
	operator = mem_add(sizeof(char), 3);
	i = 0;
	while (shell->input[i])
	{
		if (is_operator(shell->input[i]))
		{
			printf("operator found = %c\n", shell->input[i]);
			if (is_operator(shell->input[i]) && is_operator(shell->input[i + 1]))
			{
				operator = check_double_operator(shell, i, operator);
				i++;
				printf("double found = %c%c\n", shell->input[i], shell->input[i + 1]);
			}
		}
		// else if (!isspace(shell->input))
		// {
		// 	//create_word();
		// 	//i += strlen(word? - 1);
		// }
		// else
		i++;
		ft_bzero(operator, 3);
	}
	free (operator);
	
}

void	lexer(t_shell *shell)
{
	tokenizer(shell);
}