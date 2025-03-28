/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bi_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:47:31 by marvin            #+#    #+#             */
/*   Updated: 2025/03/27 20:47:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_var(char ***envp, char *var, size_t name_len, char *new)
{
	char	**env;
	int		i;

	env = *envp;
	i = 0;
	while (env[i] != NULL)
	{
		if (strncmp(env[i], var, name_len) == 0 && env[i][name_len] == '=')
		{
			free(env[i]);
			env[i] = new;
			return (0);
		}
		i++;
	}
	*envp = env;
	return (0);
}

int	update_env_var(char ***envp, char *var_name, char *value)
{
	char	**env;
	char	*new_entry;
	size_t	name_len;
	size_t	env_size;

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
	char	*home_dir;
	char	*target_dir;

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
		return (error_handler(" too many arguments", 1));
	if (chdir(target_dir) != 0)
		return (error_handler("cd: No such file or directory", 1));
	return (0);
}

int	ft_cd(char **str, char ***envp)
{
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];
	int		ret;

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
