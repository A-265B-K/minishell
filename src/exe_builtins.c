/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:00:32 by marvin            #+#    #+#             */
/*   Updated: 2025/03/23 14:00:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_pwd(void)
{
	printf("%s\n", getcwd(NULL, 0));
	return (0);
}

int	is_flag(char *str)
{
    int i;

    i = 1;
    if (str[0] != '-')
        return false;
    while (str[i])
    {
        if (str[i] != 'n')
            return false;
        i++;
    }
    return true;
}

int ft_echo(char **params)
{
    int	flag;
    int i;

    flag = 1;
    i = 0;
	if (!params || !params[i])
	{
		printf("\n");
		return (0);
	}
    while (params[i] && is_flag(params[i]))
    {
        flag = 0;
        i++;
    }
    while (params[i])
    {
        printf("%s", params[i]);
        if (params[i + 1])
            printf(" ");
        i++;
    }
    if (flag > 0)
		printf("\n");
	return (0);
}

int	ft_env(t_shell *shell)
{
	int	i;

	i = 0;

	while (shell->envp[i])
	{
		printf("%s\n", shell->envp[i]);
		i++;
	}
	return (0);
}

char	**add_new_var(char **envp, char *new_var, int count)
{
    char **new_envp;
    int i;

    new_envp = malloc(sizeof(char *) * (count + 2));
	if (!new_envp)
		return (NULL);
    i = 0;
    while (envp[i])
    {
        new_envp[i] = envp[i];
        i++;
    }
    new_envp[i] = ft_strdup(new_var);
    new_envp[i + 1] = NULL;
    return (new_envp);
}

int count_env_vars(char **envp)
{
    int count;

    count = 0;
    while (envp[count])
        count++;
    return (count);
}

char **duplicate_envp(char **envp, int count)
{
    char **new_envp;
    int i;

    new_envp = malloc(sizeof(char *) * (count + 1));
    i = 0;
    while (i < count)
    {
        new_envp[i] = envp[i];
        i++;
    }
    new_envp[count] = NULL;
    return (new_envp);
}

void sort_envp(char **sorted_envp, int count)
{
    int i;
    int j;
    char *temp;

    i = 0;
    while (i < count - 1)
    {
        j = i + 1;
        while (j < count)
        {
            if (strcmp(sorted_envp[i], sorted_envp[j]) > 0)
            {
                temp = sorted_envp[i];
                sorted_envp[i] = sorted_envp[j];
                sorted_envp[j] = temp;
            }
            j++;
        }
        i++;
    }
}

void print_sorted_envp(char **sorted_envp)
{
    int i;

    i = 0;
    while (sorted_envp[i])
    {
        printf("declare -x %s\n", sorted_envp[i]);
        i++;
    }
}

void print_env_sorted(char **envp)
{
    int count;
    char **sorted_envp;

    count = count_env_vars(envp);
    sorted_envp = duplicate_envp(envp, count);
    sort_envp(sorted_envp, count);
    print_sorted_envp(sorted_envp);
    free(sorted_envp);
}

int get_var_name_len(char *new_var)
{
    int len;

    len = 0;
    while (new_var[len] && new_var[len] != '=')
        len++;
    return (len);
}

int find_var_index(char **envp, char *new_var, int len)
{
    int i;

    i = 0;
    while (envp[i])
    {
        if (strncmp(envp[i], new_var, len) == 0 && envp[i][len] == '=')
            return (i);
        i++;
    }
    return (-1);
}

int	valid_id_check(const char *name)
{
	int	i;
	int	alph_flag;

	i = 0;
	alph_flag = 0;

	if (!name[0])
		return (0);
	if (name[0] == '=')
		return (0);
	while (name[i] && name[i] != '=')
	{
		if ((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z'))
			alph_flag = 1;
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	if (!alph_flag)
		return (0);
	return (1);
}

int	set_env_var(char ***envp, char *new_var)
{
    int 	len;
    int 	id;
    char 	**new_envp;

	if (!new_var || !valid_id_check(new_var))
		return (ft_putstr_fd(" not a valid identifier\n", STDERR_FILENO), 1);
    len = get_var_name_len(new_var);
    id = find_var_index(*envp, new_var, len);
    if (id != -1)
    {
        free((*envp)[id]);
        (*envp)[id] = ft_strdup(new_var);
		return (1);
    }
    else
    {
        new_envp = add_new_var(*envp, new_var, count_env_vars(*envp));
		if (!new_envp)
			return(perror("malloc fail"), 1);
        free(*envp);
        *envp = new_envp;
    }
	return (0);
}

int	ft_export(char **cmd, char ***envp)
{
	int	i;
	int	exitcode;

	exitcode = 0;
	i = 0;
    if (!cmd || !cmd[0])
	{
        print_env_sorted(*envp);
	}
    else
	{
		while (cmd[i])
		{
        	exitcode = set_env_var(envp, cmd[i]);
			i++;
		}
	}
	return (exitcode);
}

// int	ft_export(char **params)
// {
// 	int		i;
// 	int		exitcode;
// 	char	**export_var; // add memory safety

// 	i = -1;
// 	exitcode = 0;
// 	if (!params[0])
// 		ft_env();
// 	else
// 	{
// 		while (params[++i])
// 		{
// 			export_var = ft_split(params[i], '=');
// 			exitcode = ft_setenv(export_var[0], export_var[1]);
// 			free(export_var);
// 		}
// 	}
// 	return (exitcode);
// }

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

// int	ft_cd(char	**params)
// {
// 	char	curpath[PATH_MAX];
// 	char	dir_operand[PATH_MAX];
// 	char	temp[PATH_MAX];
// 	char	*home;

// 	home = NULL;	
// 	ft_bzero(curpath, PATH_MAX);
// 	ft_bzero(dir_operand, PATH_MAX);
// 	ft_bzero(temp, PATH_MAX);
// 	if ((!params || !params[0]) && !home)
// 		return (1);
// 	if (params[1])
// 	{
// 		dprintf(2, " too many arguments");
// 		return (1);
// 	}
// 	if (!params)
// 		ft_strlcpy(dir_operand, home, PATH_MAX);
// 	ft_strlcpy(dir_operand, params[0], PATH_MAX);
// 	if (dir_operand[0] == '/')
// 		ft_strlcpy(curpath, dir_operand, PATH_MAX);
// 	else
// 	{
// 		if (!(ft_strncmp(dir_operand, ".", 1) || ft_strncmp(dir_operand, "..", 2)))
// 		{
// 				printf("meow\n");
// 		}
// 		// Fix env variables
// 		ft_strlcpy(curpath, dir_operand, PATH_MAX);
// 	}
// 	if (curpath[0] != '/')
// 	{
// 		ft_strlcpy(temp, getcwd(NULL, 0), PATH_MAX);
// 		if (temp[strlen(temp)] != '/')
// 			temp[strlen(temp) + 1] = '/';
// 		strcat(temp, curpath);
// 		ft_strlcpy(curpath, temp, 0);
// 	}
// 	if (chdir(curpath) == -1)
// 	{
// 		dprintf(2, "cd: No such file or directory\n");
// 		return (1);
// 	}

// 	return (0);
// }

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
	if (!params)
		exit(exitcode);
	if (!params[0])
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

int	find_var(char ***envp, char *var_name, size_t name_len, char *new_entry)
{
	char	**env;
	int		i;

	env = *envp;
	i = 0;
	while (env[i] != NULL)
    {
        if (strncmp(env[i], var_name, name_len) == 0 && env[i][name_len] == '=')
        {
            free(env[i]);
            env[i] = new_entry;
            return (0);
        }
        i++;
    }
    *envp = env;
	return (0);
}

int update_env_var(char ***envp, char *var_name, char *value)
{
    char **env;
    char *new_entry;
    size_t name_len;
    size_t env_size;

    env = *envp;
    name_len = ft_strlen(var_name);
    env_size = 0;
    while (env[env_size] != NULL)
        env_size++;
    new_entry = malloc(name_len + ft_strlen(value) + 2);
    if (new_entry == NULL)
        return (error_handler("malloc @ update_env_var", -1));
    ft_memcpy(new_entry, var_name, name_len);
    new_entry[name_len] = '=';
    ft_memcpy(new_entry + name_len + 1, value, ft_strlen(value) + 1);
    return (find_var(envp, var_name, name_len, new_entry));
}

int	check_chdir(char **str)
{
	char *home_dir;
	char *target_dir;

	if (!str || !str[0])
    {
        home_dir = getenv("HOME");
        if (home_dir == NULL)
            return (error_handler("cd: HOME not set", 1));
        target_dir = home_dir;
    }
    else if (str[0] && strcmp(str[0], "-") == 0 && !str[1])
    {
        target_dir = getenv("OLDPWD");
        if (target_dir == NULL)
            return (error_handler("cd: OLDPWD not set", 1));
    }
	else if (str[0] && !str[1])
		target_dir = str[0];
	else
		return(error_handler("too many arguments", 1));
	if (chdir(target_dir) != 0)
		return (error_handler("cd: No such file or directory", 1));
	return (0);
}

int ft_cd(char **str, char ***envp)
{
    char old_pwd[PATH_MAX];
    char new_pwd[PATH_MAX];
	int ret;

    if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
		return (error_handler("cd: getcwd error 1", 1));
	if (check_chdir(str))
		return (1);
    if (getcwd(new_pwd, sizeof(new_pwd)) == NULL)
        return (error_handler("cd", 1));
    ret = 0;
    if (update_env_var(envp, "OLDPWD", old_pwd) < 0)
        ret = 1;
    if (update_env_var(envp, "PWD", new_pwd) < 0)
        ret = 1;
    if (ret == 0 && (str && str[0]) && strcmp(str[0], "-") == 0)
        printf("%s\n", new_pwd);
    return (ret);
}

int	execute_builtin(t_shell *shell, t_commands *cmd)
{
	if (!ft_strcmp2(cmd->builtin, "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp2(cmd->builtin, "echo"))
		return (ft_echo(cmd->str));
	else if (!ft_strcmp2(cmd->builtin, "cd"))
		return (ft_cd(cmd->str, &shell->envp));
	else if (!ft_strcmp2(cmd->builtin, "export"))
		return (ft_export(cmd->str, &shell->envp));
	else if (!ft_strcmp2(cmd->builtin, "unset"))
		return (ft_unsetenv(cmd->str, shell));
	else if (!ft_strcmp2(cmd->builtin, "env"))
		return (ft_env(shell));
	else if (!ft_strcmp2(cmd->builtin, "exit"))
		ft_exit(cmd->str, shell->exitcode);
	return (-1);
}