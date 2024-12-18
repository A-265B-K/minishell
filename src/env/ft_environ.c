

# include <minishell.h>

extern char **environ;

int	arraylen(char **array)
{
	size_t len;

	len = 0;
	while (array[len])
		len += 1;
	return (len);
}

char **ft_arraycopy(char **array)
{
	int		len;
	char	**out;

	len = arraylen(array);
	out = malloc(len * sizeof(char *) + 1);
	if (!out)
		return (NULL);
	bzero(out, len + 1);
	while (--len >= 0)
		out[len] = strdup(array[len]);
	return (out);
}

const char *const *const	*env_holder(void)
{
	static char **env;

	if (!env)
		env = ft_arraycopy(environ);
	return ((const char *const *const *)&env);
}
	

int	ft_setenv(const char *name)
{
}

int	ft_unsetenv(const char *name)
{
}

char	*ft_getenv(const char *name)
{
	int	i;
	const char *const	env;

	env = env_holder();
	i = -1;
	while (env[++i])
		if (ft_strncmp(env[i], name, ft_strlen(env[i]))
				return (ft_strdup(&env[i][ft_strlen(env[i]) + 1]);
	return (NULL);
}
