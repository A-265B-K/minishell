/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 21:32:01 by marvin            #+#    #+#             */
/*   Updated: 2025/03/27 21:32:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_shell(t_shell *shell)
{
	if (shell)
	{
		if (shell->input)
		{
			free(shell->input);
			shell->input = NULL;
		}
		if (shell->lex)
		{
			free_tokens(&shell->lex);
			shell->lex = NULL;
		}
		if (shell->tokenized)
		{
			free_tokens(&shell->tokenized);
			shell->tokenized = NULL;
		}
		if (shell->com_struct)
		{
			free_command_list(shell->com_struct);
			shell->com_struct = NULL;
		}
		shell->heredoc_id = 0;
	}
}

void	close_shell(t_shell *shell)
{
	if (shell)
	{
		if (shell->envp)
			free_double((char **)shell->envp);
		if (shell->input)
			free(shell->input);
		if (shell->prompt)
			free(shell->prompt);
		if (shell->com_struct)
		{
			free_command_list(shell->com_struct);
			shell->com_struct = NULL;
		}
		if (shell->lex)
			free_tokens(&shell->lex);
		if (shell->tokenized)
			free_tokens(&shell->tokenized);
		if (shell->cur_pwd)
			free (shell->cur_pwd);
		if (shell->old_pwd)
			free(shell->old_pwd);
		free (shell);
	}
}
