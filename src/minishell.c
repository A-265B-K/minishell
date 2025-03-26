/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:52:23 by alkuijte          #+#    #+#             */
/*   Updated: 2025/03/25 23:22:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_prompt(t_shell *shell)
{
	char	*prompt_line;

    // printf("cwd = %s\noldcwd = %s\n", shell->)
	if (shell->prompt)
		free(shell->prompt);
	prompt_line = env_get("USER", shell->envp);
	prompt_line = free_join(prompt_line, "@", true, false);
	prompt_line = free_join(prompt_line, env_get("PWD", shell->envp), 1, 1);
	prompt_line = free_join(prompt_line, ": ", true, false);
	shell->prompt = ft_strdup(prompt_line);
	free (prompt_line);
}

t_shell	*shell_init(char **envp)
{
	t_shell	*shell;

	shell = mem_add(1, sizeof(t_shell));
	shell->envp = alloc_double(envp);
    shell->cur_pwd = env_get("PWD", shell->envp);
    shell->old_pwd = env_get("OLDPWD", shell->envp);
    shell->heredoc_id = 0;
	return (shell);
}
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



int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	if (argc > 1 || argv[1])
	{
		printf("This program does not take arguments\n");
		exit (0);
	}
    shell = shell_init(envp);
	while (1)
	{
		set_prompt(shell);
		shell->input = readline(shell->prompt);
		if (shell->input == NULL)
			break ;
        if (shell->input[0])
        {
		    if (!lexer(shell))
			    break ;
		    if (parser(shell))
                break ;
		    if (ft_strlen(shell->input) > 0)
			    add_history(shell->input);
		    execute(shell);
        }
		reset_shell(shell);
	}
	close_shell(shell);
	exit(0);
}
