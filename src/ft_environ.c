

# include <minishell.h>

extern char **environ;
static char ***env_holder(void);

int	arraylen(char **array)
{
	size_t len;

	len = 0;
	while (array[len])
		len += 1;
	return (len);
}

void	free_array(char **array, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		free(array[i]);
	free(array);
}

static int	find_env_index(const char *name, t_shell *shell)
{
	int		i;
	size_t	len;

	len = ft_strlen(name);
	i = 0;
	while (shell->envp[i])
	{
		if (!strncmp(shell->envp[i], name, len))
			return (i);
		i++;
	}
	return (-1);
}

char **ft_arraycopy(char **array)
{
	int		len;
	char	**out;
	int		i;

	len = arraylen(array);
	out = malloc((len + 1) * sizeof(char *));
	if (!out)
		return (NULL);
	i = -1;
	while (++i < len)
	{
		out[i] = strdup(array[i]);
		if (!out[i])
		{
			while (--i >= 0)
				free(out[i]);
			free(out);
			return (NULL);
		}
	}
	out[len] = NULL;
	return (out);
}

static char ***env_holder(void)
{
	static char **env = NULL;

	if (!env)
		env = ft_arraycopy(environ);
	return (&env);
}

const char *const *borrow_env(void)
{
	return ((const char *const *)*env_holder());
}

int	valid_identifier_check(const char *name)
{
	int	i;
	int	alph_flag;

	i = -1;
	alph_flag = 0;

	if (!name[0])
		return (0);
	if (name[0] == '=')
		return (0);
	while (name[++i])
	{
		if ((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z'))
			alph_flag = 1;
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
	}
	if (!alph_flag)
		return (0);
	return (1);
}

int	ft_unsetenv(char **params, t_shell *shell)
{
	int	i;
	char	*name;

	if (!params)
		return (0);
	name = ft_strdup(params[0]);
	if (!ft_strncmp(name, "", 1))
		return (0);
	if (!ft_strncmp(name, "HOME", 4) || !ft_strncmp(name, "PATH", 4) || !ft_strncmp(name, "SHELL", 5))
		return (0);
	i = find_env_index(name, shell);
	if (i == -1)
		return (0);
	free(shell->envp[i]);
	while (shell->envp[i])
	{
		shell->envp[i] = shell->envp[i + 1];
		i += 1;
	}
	free(shell->envp[i]);
	free(name);
	return (0);
}

char	*ft_getenv(const char *name, t_shell *shell)
{
	int	i;
	const char	*env_var;
	size_t		name_len;

	name_len = ft_strlen(name);
	i = -1;
	while (shell->envp[++i])
	{
		env_var = shell->envp[i];
		if (!ft_strncmp(env_var, name, name_len))
				return (ft_strdup(&env_var[name_len + 1]));
	}
	return (NULL);
}
