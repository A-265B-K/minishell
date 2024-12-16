# include <minishell.h>

char *home = NULL;

int	ft_cd(int	fd, void *arg)
{
	char	curpath[PATH_MAX];
	char	dir_operand[PATH_MAX];
	char	temp[PATH_MAX];

	char *in_operand = (char *)arg;
	ft_bzero(curpath, PATH_MAX);
	ft_bzero(dir_operand, PATH_MAX);
	ft_bzero(temp, PATH_MAX);
	// set OLDPWD
	if ((!in_operand || !in_operand[0]) && !home)
		return (1);
	if (!in_operand)
		ft_strlcpy(dir_operand, home, PATH_MAX);
	printf("In operand: %s\n", in_operand);
	ft_strlcpy(dir_operand, in_operand, PATH_MAX);
	if (dir_operand[0] == '/')
		ft_strlcpy(curpath, dir_operand, PATH_MAX);
	else
	{
		if (!(ft_strncmp(dir_operand, ".", 1) || ft_strncmp(dir_operand, "..", 2)))
		{
				printf("meow\n");
		}
		ft_strlcpy(curpath, dir_operand, PATH_MAX);
	}
	printf("In operand: %s\n", curpath);
	if (curpath[0] != '/')
	{
		ft_strlcpy(temp, getcwd(NULL, 0), PATH_MAX);
		if (temp[strlen(temp)] != '/')  // potentially add safeguard here
			temp[strlen(temp) + 1] = '/';
		strcat(temp, curpath);
		ft_strlcpy(curpath, temp, 0);
	}
	// set PWD
	ft_printf_fd(fd, "Current path: %s\n", curpath);
	if (chdir(curpath) == -1) // implement safeguard
		ft_printf_fd(fd, "cd: no such file or directory: %s\n", curpath);
	printf("%s\n", getcwd(NULL, 0));
	return (1);
}
