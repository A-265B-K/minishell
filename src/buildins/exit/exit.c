
#include "../../../include/minishell.h"

int	b_exit(int argc, char **argv, char **envp, t_shell *shell)
{
	(void)envp;
	(void)shell;
	debug("buildin_exit placeholder to set exitcode");
	if (argc > 1)
		return (atoi(argv[1]));
	return (0);
}
