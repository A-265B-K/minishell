/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahornstr <ahornstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:52:23 by alkuijte          #+#    #+#             */
/*   Updated: 2024/12/20 13:37:48 by ahornstr         ###   ########.fr       */
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
	prompt_line = ft_strjoin(prompt_line, " :");
	shell->prompt = prompt_line;
}

t_shell	*shell_init(char **envp)
{
	t_shell *shell;
	shell = mem_add(1, sizeof(t_shell));
	shell->envp = alloc_double(envp);
	set_prompt(shell);
	
	return (shell);
}

void	close_shell(t_shell *shell)
{
	if (shell->envp)
		free_double((char **)shell->envp);
	free (shell);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell *shell;
	((void)argc, (void)argv);
	shell = shell_init(envp);
	while ((shell->input = readline(shell->prompt)) != NULL)
	{
		lexer(shell);
		if (strlen(shell->input) > 0)
		{
			add_history(shell->input);
			free(shell->input);
		}
		parser(shell);
	}
	close_shell(shell);
	return (0);
}

