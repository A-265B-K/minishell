
#include "../../../include/minishell.h"

int	cd(int argc, char **argv, char **envp, t_shell *shell)
{
	char		*path;
	char		*pwd;
	char		*str;

	if (argc == 1)
		path = env_get("HOME", envp);
	else
		path = argv[1];
	pwd = free_join("OLDPWD=", getcwd(NULL, 0), false, true);
	if (chdir(path) == 0)
	{
		env_set(pwd, shell->envp);
		pwd = free_join("PWD=", getcwd(NULL, 0), false, true);
		env_set(pwd, shell->envp);
		set_prompt(shell->envp, shell);
		return (EXIT_SUCCESS);
	}
	str = ft_strjoin(CD_ERR, path);
	error(str);
	return (free(str), free(pwd), EXIT_FAILURE);
}
