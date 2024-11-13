
#include "../../../include/minishell.h"

void	export_copy(char **env_temp, t_shell *shell, int i)
{
	env_temp[i] = (char *)mem_add(ft_strlen(shell->envp[i]) + 1, sizeof(char));
	strcpy(env_temp[i], shell->envp[i]);
}

void	export_switch(char **env_temp, t_shell *shell, int j)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < ft_strarrlen(shell->envp))
	{
		j = i + 1;
		while (j < ft_strarrlen(shell->envp))
		{
			if (ft_strncmp(env_temp[i], env_temp[j], ft_strlen(env_temp[i])) > 0)
			{
				tmp = env_temp[i];
				env_temp[i] = env_temp[j];
				env_temp[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	b_export(int argc, char **argv, char **envp, t_shell *shell)
{
	int		i;
	int		j;
	char	**env_temp;

	(void)argc;
	(void)envp;
	i = 0;
	j = 0;
	if (ft_strarrlen(argv) > 1)
	{
		export_add(argv, shell);
		return (0);
	}
	env_temp = (char **)mem_add(ft_strarrlen(shell->envp) + 1, sizeof(char *));
	while (i < (ft_strarrlen(shell->envp)))
		export_copy(env_temp, shell, i++);
	env_temp[i] = NULL;
	export_switch(env_temp, shell, j);
	print_double(env_temp);
	free_double(env_temp);
	return (0);
}
