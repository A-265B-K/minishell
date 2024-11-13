
#include "../../../include/minishell.h"
/**
 * @brief env with no options or arguments
 * 
 * @param envp 
 */
int	env(int argc, char **argv, char **envp, t_shell *shell)
{
	int	i;

	(void)argv;
	(void)argc;
	(void)shell;
	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '=') == NULL)
			i++;
		if (envp[i] != NULL)
			printf("%s\n", envp[i]);
		if (envp[i] != NULL)
			i++;
	}
	return (0);
}
