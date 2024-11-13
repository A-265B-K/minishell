
#include "../../../include/minishell.h"

int	unset_find_line(char *argv, char **s_envp)
{
	int		i;
	size_t	j;

	j = 0;
	i = 0;
	while (s_envp[i])
	{
		j = 0;
		while (s_envp[i][j] != '=' && s_envp[i][j] != '\0')
			j++;
		if (!ft_strncmp(argv, s_envp[i], j) && j == ft_strlen(argv))
			return (i);
		i++;
	}
	return (-1);
}

void	unset_line(char ***envp, int line)
{
	char	**temp;

	temp = array_remove_line(*envp, line);
	free_double(*envp);
	*envp = temp;
}

char	**array_remove_line(char **strs, int line)
{
	int		i;
	int		j;
	char	**ret;

	ret = mem_add(ft_strarrlen(strs), sizeof(char *));
	if (!ret)
		return (0);
	i = 0;
	j = 0;
	while (strs[i])
	{
		if (i == line)
			i++;
		if (strs[i])
		{
			ret[j] = ft_strdup(strs[i]);
			i++;
			j++;
		}
		if (i == line)
			i++;
	}
	ret[j] = 0;
	return (ret);
}

int	unset(int argc, char **argv, char **envp, t_shell *shell)
{
	int	i;
	int	line;

	i = 1;
	(void)shell;
	(void)envp;
	if (argc == 1)
		printf("unset: not enough arguments\n");
	while (i < argc)
	{
		line = unset_find_line(argv[i], shell->envp);
		if (line >= 0)
			unset_line(&shell->envp, line);
		i++;
	}
	return (0);
}
