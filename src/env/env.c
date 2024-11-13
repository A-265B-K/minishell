
#include "../../include/minishell.h"

char	**env_get_searchpaths(char *envp[])
{
	int		i;
	char	**searchpaths;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			searchpaths = ft_split(envp[i] + 5, ':');
			if (!searchpaths)
				return (NULL);
			return (searchpaths);
		}
		i++;
	}
	return (NULL);
}

char	*env_get(char *str, char *envp[])
{
	int	i;
	int	length;

	i = 0;
	length = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], str, ft_strlen(str)) == 0
			&& envp[i][ft_strlen(str)] == '=')
		{
			while (envp[i][length] != '\0')
				length++;
			return (ft_substr(envp[i], ft_strlen(str) + 1, length));
		}
		i++;
	}
	return (ft_memcpy(mem_add(1, sizeof(char)), "", 1));
}

void	env_replace(char **old_envp, const char *replace)
{
	char	*new_env;

	new_env = ft_strdup(replace);
	free(*old_envp);
	*old_envp = new_env;
}

char	**array_add_back(char **strs, const char *str)
{
	int		i;
	char	**ret;

	ret = mem_add(ft_strarrlen(strs) + 2, sizeof(char *));
	if (!ret)
		return (0);
	i = 0;
	while (strs[i])
	{
		ret[i] = ft_strdup(strs[i]);
		i++;
	}
	ret[i++] = ft_strdup(str);
	ret[i] = 0;
	return (ret);
}

bool	env_add(char *str, char ***envp)
{
	char	**new_env;

	new_env = array_add_back(*envp, str);
	free_double(*envp);
	*envp = new_env;
	return (true);
}

bool	env_set(char *str, char *envp[])
{
	int		i;
	char	**j;

	i = 0;
	j = ft_split(str, '=');
	while (envp[i])
	{
		if (ft_strncmp(envp[i], j[0], ft_strlen(j[0])) == 0)
		{
			free(envp[i]);
			envp[i] = str;
			free(j[0]);
			free(j[1]);
			free(j);
			return (true);
		}
		i++;
	}
	free(j[0]);
	free(j[1]);
	free(j);
	return (env_add(str, &envp));
}
