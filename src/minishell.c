/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/13 12:52:23 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/03/28 13:09:09 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_prompt(t_shell *shell)
{
	char	*prompt_line;

	if (shell->prompt)
		free(shell->prompt);
	prompt_line = ft_env_get("USER", shell->envp);
	prompt_line = free_join(prompt_line, "@", true, false);
	prompt_line = free_join(prompt_line, ft_env_get("PWD", shell->envp), 1, 1);
	prompt_line = free_join(prompt_line, ": ", true, false);
	shell->prompt = ft_strdup(prompt_line);
	free (prompt_line);
}

t_shell	*shell_init(char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->envp = alloc_double(envp);
	if (!shell->envp)
		return (NULL);
	shell->cur_pwd = ft_env_get("PWD", shell->envp);
	if (!shell->cur_pwd)
		return (NULL);
	shell->old_pwd = ft_env_get("OLDPWD", shell->envp);
	if (!shell->old_pwd)
		return (NULL);
	shell->exitcode = 0;
	shell->com_struct = NULL;
	shell->tokenized = NULL;
	shell->lex = NULL;
	shell->input = NULL;
	shell->prompt = NULL;
	shell->quoted = 0;
	shell->heredoc_id = 0;
	return (shell);
}

int	run_shell(t_shell *shell)
{
	int	code;

	code = lexer(shell);
	if (code == 1)
		return (1);
	if (code == 2)
		return (0);
	code = parser(shell);
	if (code == 1)
		return (1);
	if (code == 2)
		return (0);
	if (ft_strlen(shell->input) > 0)
		add_history(shell->input);
	execute(shell);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	if (argc > 1 || argv[1])
		exit (error_handler("This program does not take arguments", 1));
	shell = shell_init(envp);
	if (!shell)
		exit(1);
	setup_signals();
	while (1)
	{
		reset_shell(shell);
		set_prompt(shell);
		shell->input = readline(shell->prompt);
		if (shell->input == NULL)
			break ;
		if (shell->input[0])
		{
			if (run_shell(shell))
				break ;
		}
	}
	close_shell(shell);
	exit(0);
}
