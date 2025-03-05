/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/05 18:12:05 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/03/05 18:24:26 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_pwd(void)
{
	printf("%s\n", getcwd(NULL, 0));
	return (0);
}

int	ft_echo(char **params)
{
	int	i;
	int	j;

	i = 0;
	if (params && params[0])
	{
		while (params[i])
		{
			j = 0;
			if (i > 0)
				printf(" ");
			printf("%s", params[i] + j);
			i += 1;
		}
	}
	printf("\n");
	return (0);
}

int	ft_env(void)
{
	const char *const *const	env = borrow_env();
	int							i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i += 1;
	}
	return (0);
}

int	ft_export(char **params)
{
	int		i;
	int		exitcode;
	char	**export_var; // add memory safety

	i = -1;
	exitcode = 0;
	if (!params[0])
		ft_env();
	else
	{
		while (params[++i])
		{
			export_var = ft_split(params[i], '=');
			exitcode = ft_setenv(export_var[0], export_var[1]);
			free(export_var);
		}
	}
	return (exitcode);
}

int	ft_isstrnum(char *str) // move to libft
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
			break ;
		}
		str += 1;
	}
	return (flag);
}

int	ft_cd(char	**params)
{
	char	curpath[PATH_MAX];
	char	dir_operand[PATH_MAX];
	char	temp[PATH_MAX];
	char	*home;

	home = NULL;	
	ft_bzero(curpath, PATH_MAX);
	ft_bzero(dir_operand, PATH_MAX);
	ft_bzero(temp, PATH_MAX);
	if ((!params || !params[0]) && !home)
		return (1);
	if (params[1])
	{
		dprintf(2, " too many arguments");
		return (1);
	}
	if (!params)
		ft_strlcpy(dir_operand, home, PATH_MAX);
	ft_strlcpy(dir_operand, params[0], PATH_MAX);
	if (dir_operand[0] == '/')
		ft_strlcpy(curpath, dir_operand, PATH_MAX);
	else
	{
		if (!(ft_strncmp(dir_operand, ".", 1) || ft_strncmp(dir_operand, "..", 2)))
		{
				printf("meow\n");
		}
		// Fix env variables
		ft_strlcpy(curpath, dir_operand, PATH_MAX);
	}
	if (curpath[0] != '/')
	{
		ft_strlcpy(temp, getcwd(NULL, 0), PATH_MAX);
		if (temp[strlen(temp)] != '/')
			temp[strlen(temp) + 1] = '/';
		strcat(temp, curpath);
		ft_strlcpy(curpath, temp, 0);
	}
	if (chdir(curpath) == -1)
	{
		dprintf(2, "cd: No such file or directory\n");
		return (1);
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2) // move libft
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)(*s1) - (unsigned char)(*s2));
}

// free!!!
void	ft_exit(char **params, int exitcode)
{
	if (!params && !params[0])
		exit(exitcode);
	if (params[1])
	{
		dprintf(2, " too many arguments");
		exit(1);
	}
	if (!ft_isstrnum(params[0]))
	{
		dprintf(2, " numeric argument required");
		exit(2);
	}
	exitcode = ft_atoi(params[0]);
	exit(exitcode);
}

int	execute_builtin(t_shell *shell, t_commands *cmd)
{
	if (!ft_strcmp2(cmd->builtin, "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp2(cmd->builtin, "echo"))
		return (ft_echo(cmd->str));
	else if (!ft_strcmp2(cmd->builtin, "cd"))
		return (ft_cd(cmd->str));
	else if (!ft_strcmp2(cmd->builtin, "export"))
		return (ft_export(cmd->str));
	else if (!ft_strcmp2(cmd->builtin, "unset"))
		return (ft_unsetenv(cmd->str));
	else if (!ft_strcmp2(cmd->builtin, "env"))
		return (ft_env());
	else if (!ft_strcmp2(cmd->builtin, "exit"))
		ft_exit(cmd->str, shell->exitcode);
	return (-1);
}
