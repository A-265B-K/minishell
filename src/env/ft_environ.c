

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
    int        len;
    char    **out;

    len = arraylen(array);
    out = malloc(len * sizeof(char *) + 1);
    if (!out)
        return (NULL);
    bzero(out, len + 1);
    while (--len >= 0)
        out[len] = strdup(array[len]);
    return (out);
}

char	***env_holder(void)
{
	const char **env;

	if (!env)
		env = ft_arraycopy(environ);
	return (env);
}
	

int	ft_setenv(const char *name)
{
}

int	ft_unsetenv(const char *name)
{
}
