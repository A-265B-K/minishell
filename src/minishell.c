#include "../include/minishell.h"

void	ft_list_semi_clear(t_list **lst)
{
	t_list	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
}

/**
 * @brief Free the shell struct && clear readline history.
 * 
 * @param shell 
 * @param all 
 * @return int 
 */
int	clean_exit(t_shell *shell)
{
	int	exitcode;

	exitcode = shell->exitcode;
	free(shell->input);
	rl_clear_history();
	ft_lstclear(&shell->tasks, free_t_tasks);
	ft_lstclear(&shell->tokens, free_t_token);
	free_double((char **)shell->envp);
	free(shell->history_state);
	free(shell->prompt);
	free(shell);
	debug("Clean exit OK");
	return (exitcode);
}

char	**allocated_envp(char **envp)
{
	char	**new;
	int		i;

	new = mem_add(ft_strarrlen(envp) + 1, sizeof(char *));
	i = 0;
	while (envp[i])
	{
		new[i] = ft_strdup(envp[i]);
		i++;
	}
	return (new);
}

/**
 * @brief Initialize the shell struct
 * Add environment variables to the shell struct.
 * Set the shell name.
 * Set the debug mode.
 * Set the exitcode to EXIT_FAILURE.
 * 
 * @param argc Argument count.
 * @param argv Argument vector.
 * @param envp Environment variables.
 * @return t_shell* 
 */
static t_shell	*shell_init(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	shell = mem_add(1, sizeof(t_shell));
	shell->envp = allocated_envp(envp);
	shell->exitcode = EXIT_FAILURE;
	shell->exit = false;
	shell->debug = DEBUG;
	shell->tasks = NULL;
	if (argc > 1 && ft_strncmp(argv[1], "-d", ft_strlen(argv[1])) == 0)
		shell->debug = true;
	debug("Shell initialized OK");
	return (shell);
}

/**
 * @brief Minishell main function.
 * @details
 * @file minishell.c
 * @param argc Argument count.
 * @param argv Argument vector.
 * @param envp Environment variables.
 * @return int exitcode	EXIT_SUCCESS or EXIT_FAILURE
 */
int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	shell = shell_init(argc, argv, envp);
	signal_init();
	history_init(shell);
	readline_init(shell);
	shell->input = readline(shell->prompt);
	while (shell->input)
	{
		history_add(shell->input, shell);
		tokenizer(shell);
		parser(shell);
		if (execute(shell) == EXIT)
			break ;
		ft_lstclear(&shell->tasks, free_t_tasks);
		ft_lstclear(&shell->tokens, free_t_token);
		free(shell->input);
		signal(SIGINT, signal_handler);
		shell->input = readline(shell->prompt);
	}
	return (clean_exit(shell));
}
