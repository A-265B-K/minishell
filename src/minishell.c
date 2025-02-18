/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:52:23 by alkuijte          #+#    #+#             */
/*   Updated: 2025/02/18 17:49:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_prompt(t_shell *shell)
{
	char	*prompt_line;

	if (shell->prompt)
		free(shell->prompt);
	prompt_line = env_get("USER", shell->envp);
	prompt_line = free_join(prompt_line, " @ ", true, false);
	prompt_line = free_join(prompt_line, env_get("PWD", shell->envp), true, true);
	prompt_line = free_join(prompt_line, " :", true, false);
	shell->prompt = ft_strdup(prompt_line);
	free (prompt_line);
}

t_shell	*shell_init(char **envp)
{
	t_shell *shell;
	shell = mem_add(1, sizeof(t_shell));
	shell->envp = alloc_double(envp);
	set_prompt(shell);
	return (shell);
}
void	reset_shell(t_shell *shell)
{
	if (shell)
	{
		if (shell->com_struct)
		{
			free_command_list(shell->com_struct);
			shell->com_struct = NULL;
		}
		if (shell->tokenized)
		{
			free_tokens(shell->tokenized);
			shell->tokenized = NULL;
		}
		if (shell->lexer_grouped)
		{
			free_tokens(shell->lexer_grouped);
			shell->lexer_grouped = NULL;
		}
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
		if (shell->tokenized)
			free_tokens(shell->tokenized);
		if (shell->lexer_grouped)
			free_tokens(shell->lexer_grouped);
		free (shell);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell *shell;
	((void)argc, (void)argv);
	shell = shell_init(envp);
	while ((shell->input = readline(shell->prompt)) != NULL)
	{
		if (!ft_strncmp(shell->input, "shellleak", 9))
			break ;
		if (!lexer(shell))
			break ;
		if (!ft_strncmp(shell->input, "lexerleak", 9))
			break ;
		if (ft_strlen(shell->input) > 0)
			add_history(shell->input);
		parser(shell);
		if (!ft_strncmp(shell->input, "parserleak", 10))
			break ;
		printf("{{{execute}}}\n");
		reset_shell(shell);
	}
	close_shell(shell);
	return (0);
}

