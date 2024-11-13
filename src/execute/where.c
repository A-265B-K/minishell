
#include "../../include/minishell.h"

char	*where(char *arg, t_shell *shell)
{
	const char	**paths = (const char **)env_get_searchpaths(shell->envp);
	char		*new_path;
	struct stat	buf;
	int			i;

	i = 0;
	new_path = NULL;
	if (stat(arg, &buf) == 0)
		new_path = ft_strdup(arg);
	else
	{
		while (paths && paths[i])
		{
			new_path = free_join(ft_strjoin(paths[i], "/"), arg, true, false);
			if (stat(new_path, &buf) == 0)
				break ;
			free(new_path);
			i++;
		}
	}
	i = 0;
	free_double((char **)paths);
	return (new_path);
}
