

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

static int	find_env_index(const char *name)
{
	int		i;
	size_t	len;
	const char *const *const env = borrow_env();

	len = ft_strlen(name);
	i = -1;
	while (env[++i])
		if (!strncmp(env[i], name, len))
			return (i);
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

const char *const
	*borrow_env(void)
{
	return ((const char *const *)*env_holder());
}
	
int ft_setenv(const char *name, const char *value)
{
	char ***const	env = env_holder();
	char **temp_env;
	char *new_var;
	int i;
	const int array_len = arraylen(*env);

	if (!name)
		return (1);
	i = -1;
	while (++i < array_len)
	{
		if (strncmp(*env[i], name, strlen(name)) == 0 && *env[i][strlen(name)] == '=')
		{
			new_var = malloc(strlen(name) + strlen(value) + 2);
			if (!new_var)
				return (1);
			snprintf(new_var, strlen(name) + strlen(value) + 2, "%s=%s", name, value);
			free(*env[i]);
			*env[i] = new_var;
			return (0);
		}
	}
	temp_env = malloc((array_len + 2) * sizeof(char *));
	if (!temp_env)
		return (1);
	i = -1;
	while (++i < array_len)
	{
		temp_env[i] = strdup(*env[i]);
		if (!temp_env[i])
		{
			free_array(temp_env, array_len + 2);
			return (1);
		}
	}
	new_var = malloc(strlen(name) + strlen(value) + 2);
	if (!new_var)
	{
		free_array(temp_env, array_len + 2);
		return (1);
	}
	snprintf(new_var, strlen(name) + strlen(value) + 2, "%s=%s", name, value);
	temp_env[array_len] = new_var;
	temp_env[array_len + 1] = NULL;
	free_array(*env, array_len);
	*env = temp_env;
	return (0);
}

int	ft_unsetenv(const char *name)
{
	int	i;
	char ***const	env = env_holder();

	i = find_env_index(name);
	if (i == -1)
		return (0);
	free(*env[i]);
	while (*env[i])
	{
		env[i] = env[i + 1];
		i += 1;
	}
	free(*env[i]);
	return (0);
}

char	*ft_getenv(const char *name)
{
	int	i;
	const char *const *const	env = borrow_env();
	const char	*env_var;
	size_t		name_len;
;
	name_len = ft_strlen(name);
	i = -1;
	while (env[++i])
	{
		env_var = env[i];
		if (!ft_strncmp(env_var, name, name_len))
				return (ft_strdup(&env_var[name_len + 1]));
	}
	return (NULL);
}
