
#include "../../include/minishell.h"

/**
 * @brief Prints the Shell struct
 * 
 * @param shell 
 */
int	b_debug(int argc, char **argv, char **envp, t_shell *shell)
{
	(void)argc;
	(void)argv;
	(void)envp;
	print_shell(shell);
	return (EXIT_SUCCESS);
}

int	builtins(int argc, char **argv, char **envp, t_shell *shell)
{
	const char			*builtins[9]
		= {"echo", "cd", "pwd", "export", "unset", "env", "exit", "debug"};
	const t_function	functions[8] = {
		b_echo, cd, pwd, b_export, unset, env, b_exit, b_debug
	};
	int					i;

	i = 0;
	while (builtins[i])
	{
		if (argv[0] && ft_strncmp(argv[0], builtins[i], ft_strlen(argv[0])) == 0)
		{
			shell->exitcode = functions[i](argc, argv, envp, shell);
			return (true);
		}
		i++;
	}
	return (false);
}

int	pwd(int argc, char **argv, char **envp, t_shell *shell)
{
	char	cwd[PATH_MAX];

	(void)argc;
	(void)argv;
	(void)envp;
	(void)shell;
	{
		ft_putendl_fd(cwd, 1);
		return (1);
	}
	return (0);
}
