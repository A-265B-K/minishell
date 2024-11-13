
#include "../../include/minishell.h"

/**
 * @brief Set or update the shell->prompt to the prompt of the shell.
 * 
 * @param envp 
 * @param shell 
 */
void	set_prompt(char *envp[], t_shell *shell)
{
	char			*name;

	if (shell->prompt)
		free(shell->prompt);
	name = YELLOW;
	name = free_join(name, env_get("USER", envp), false, true);
	name = free_join(name, NORMAL, true, false);
	name = free_join(name, " @ ", true, false);
	name = free_join(name, BLUE, true, false);
	name = free_join(name, env_get("PWD", envp), true, true);
	name = free_join(name, NORMAL, true, false);
	name = free_join(name, " 🐚 ", true, false);
	shell->prompt = name;
}

/**
 * @brief Initialize the readline library.
 * @attention This is a hack for readline local echo when in non-interavtive mode
 * @file readline.c
 */
void	readline_init(t_shell *shell)
{
	if (!isatty(STDIN_FILENO))
		rl_outstream = stdin;
	set_prompt(shell->envp, shell);
}
