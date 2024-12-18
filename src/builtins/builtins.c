# include <minishell.h>

int	ft_getcwd(int fd)
{
	ft_printf_fd(fd, "%s\n", getcwd(NULL, 0));
}

int ft_echo(int fd, char **params)
{
	int	i;
	char	*env_var;

	i = 0;
	if (params)
		while (params[++i])
		{
			if (i > 1)
				ft_printf_fd(fd, " ");
			if (params[i][0] == '$' && !params[i][1])
				ft_printf_fd(fd, "$");
			else if (params[i][0] == '$')
			{
				env_var = ft_getenv(&params[i][1]);
				if (env_var)
					dprintf(fd, "%s", env_var);
			}
			else
				ft_printf_fd(fd, "%s", params[i]);
		}
	ft_printf_fd(fd, "\n");
}

int ft_export(int fd)
{
	ft_printf_fd(fd, "*very bad computer sounds*\n");
}

int	ft_unset(int fd)
{
	ft_printf_fd(fd, "Signed. A very confused physicist\n");
}

int	ft_env(int fd)
{
	const char *const *const env = borrow_env();
	int	i;

	i = 0;
	fd = 0;
	while (env[i])
	{
		ft_printf_fd(fd, "%s\n", env[i]);
		i += 1;
	}
}

int	ft_isstrnum(char *str)
{
	int	flag;

	flag = 1;
	if (!str || *str == '\0')
		return (0);
	if (*str == '+' || *str == '-')
		str += 1;
	while (*str)
	{
		if (!ft_isdigit(*str))
		{
			flag = 0;
			break;
		}
		str += 1;
	}
	return (flag);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (unsigned char)(*s1) - (unsigned char)(*s2);
}


void	ft_exit(char **params)
{
	if (!params || !params[1])
		exit(0);
	if (params[2])
	{
		ft_printf_fd(2, " too many arguments");
		exit(1);
	}
	if (!ft_isstrnum(params[1]))
	{
		ft_printf_fd(2, " numeric argument required");
		exit(2);
	}
	exit(ft_atoi(params[1]));
}

int	function_call(int fd, char *parameters, t_shell *tstruct)
{
//	parameters += 1;
//	char *function_name = parameters[1];
//	parameters += 2;
	char **params = ft_split(parameters, ' ');
	char *function_name = params[0];
	if(!ft_strcmp(function_name, "pwd"))
			tstruct->exitcode = ft_getcwd(fd);
	else if(!ft_strcmp(function_name, "echo"))
			tstruct->exitcode =ft_echo(fd, params);
	else if(!ft_strcmp(function_name, "cd"))
			tstruct->exitcode = ft_cd(fd, params);
	else if(!ft_strcmp(function_name, "export"))
			ft_export(fd);
	else if(!ft_strcmp(function_name, "unset"))
			ft_unset(fd);
	else if(!ft_strcmp(function_name, "env"))
			ft_env(fd);
	else if(!ft_strcmp(function_name, "exit"))
			ft_exit(params);
	else 
		return (error("A non-existent function was called"));
	return (1);
}


