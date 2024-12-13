# include <minishell.h>

typedef struct {
	const char *key;
	int (*func)(void *);
}	Command;


int	ft_getcwd(void *arg)
{
	(void )arg;
	printf("%s\n", getcwd(NULL, 0));
	return (1);
}

int ft_echo()
{
	printf("Whale noises\n");
	return (1);
}

int ft_export()
{
	printf("*very bad computer sounds*\n");
	return (1);
}

int ft_unset()
{
	printf("Signed. A very confused physicist\n");
	return (1);
}

int	ft_env()
{
	printf("[jealous staring]\n");
	return (1);
}

int ft_exit(void *arg)
{
	int	exit_code;
	if (arg)
		exit_code = *(int *)arg;
	else
		exit_code = 0;
	exit(exit_code);
	return (1);
}

int	function_call(char *input, char **parameters, int size)
{
	int	i;


	Command commands[] = {
		{"pwd", ft_getcwd},
		{"cd", ft_cd},
		{"echo", ft_echo},
		{"export", ft_export},
		{"unset", ft_unset},
		{"env", ft_env},
		{"exit", ft_exit}
	};
	i = -1;
	while (++i < size)
		if (!strcmp(input, commands[i].key))
			return (commands[i].func(parameters));
	return (error_handling("A non-existent function was called"));
}


