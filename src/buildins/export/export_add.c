
#include "../../../include/minishell.h"

void	export_add(char **argv, t_shell *shell)
{
	int	i;

	i = 1;
	while (argv[i] != NULL)
	{
		if (export_check(argv))
		{
			if (dupe_check(argv[i], shell->envp) == -1)
				env_add(argv[i], &shell->envp);
			else if (dupe_check(argv[i], shell->envp) >= 0)
				env_replace((shell->envp) + dupe_check(argv[i],
						shell->envp), argv[i]);
		}
		i++;
	}
}

int	type_check(char *argv)
{
	int	i;
	int	type;

	i = 0;
	type = 0;
	while (argv[i] != '=' && argv[i] != '\0')
		i++;
	if (argv[i] == '\0')
		type = 0;
	else if (argv[i] == '=' && argv[i + 1] == '\0')
		type = 1;
	else
		type = 2;
	return (type);
}
// exit? error

char	*variable_find(char *argv)
{
	int		i;
	char	*var;

	i = 0;
	while (argv[i])
	{
		if (argv[i] == '=')
		{
			var = ft_substr(argv, 0, i);
			return (var);
		}
		i++;
	}
	var = ft_strdup(argv);
	return (var);
}

int	dupe_check(char *argv, char **envp)
{
	int		j;
	int		type;
	char	*variable;

	j = 0;
	type = type_check(argv);
	variable = variable_find(argv);
	while (envp[j])
	{
		if (type != 0)
		{
			if (ft_strncmp(variable, envp[j], ft_strlen(variable)) == 0)
				return (free(variable), j);
		}
		if (type == 0)
		{
			if (ft_strncmp(variable, envp[j], ft_strlen(variable)) == 0)
				return (free(variable), -2);
		}
		j++;
	}
	return (free (variable), -1);
}

bool	export_check(char **argv)
{
	int		i;
	int		j;

	j = 0;
	i = 1;
	while (argv[i])
	{
		if (argv[i][0] == '=')
		{
			printf(" export: `%s': not a valid identifier\n", argv[i]);
			return (false);
		}
		j = 0;
		while (argv[i][j] != '=' && argv[i][j] != '\0')
		{
			if (!ft_isalnum(argv[i][j]) && argv[i][j] != '_')
			{
				printf(" export: `%s': not a valid identifier\n", argv[i]);
				return (false);
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (argv[i])
	{
		if (argv[i][j] == '=' && argv[i][j + 1] == '\0')
			argv[i] = ft_strjoin(argv[i], "''");
		i++;
	}
	return (true);
}
