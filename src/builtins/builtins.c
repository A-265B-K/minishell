# include <minishell.h>

int ft_strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

void	ft_getcwd(int fd)
{
	ft_printf_fd(fd, "%s\n", getcwd(NULL, 0));
}

void ft_echo(int fd, char *params)
{
	if (params)
		ft_printf_fd(fd, "%s\n", params);
	else
		ft_printf_fd(fd, "\n");
}

void ft_export(int fd)
{
	ft_printf_fd(fd, "*very bad computer sounds*\n");
}

void	ft_unset(int fd)
{
	ft_printf_fd(fd, "Signed. A very confused physicist\n");
}

void	ft_env(int fd)
{
	ft_printf_fd(fd, "[jealous staring]\n");
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

void	ft_exit(char *params)
{
	if (!params)
		exit(0);
	if (ft_strchr(params, ' '))
	{
		ft_printf_fd(2, " too many arguments");
		exit(1);
	}
	if (!ft_isstrnum(params))
	{
		ft_printf_fd(2, " numeric argument required");
		exit(2);
	}
	exit(ft_atoi(params));
}

int	function_call(int fd, char *parameters)
{
//	parameters += 1;
//	char *function_name = parameters[1];
//	parameters += 2;
	char **params = get_function_name(parameters);
	char *function_name = params[0];
	if(!ft_strcmp(function_name, "pwd"))
			ft_getcwd(fd);
	else if(!ft_strcmp(function_name, "echo"))
			ft_echo(fd, params[1]);
	else if(!ft_strcmp(function_name, "export"))
			ft_export(fd);
	else if(!ft_strcmp(function_name, "unset"))
			ft_unset(fd);
	else if(!ft_strcmp(function_name, "env"))
			ft_env(fd);
	else if(!ft_strcmp(function_name, "exit"))
			ft_exit(params[1]);
	else 
		return (error("A non-existent function was called"));
	return (1);
}


