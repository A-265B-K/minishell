
#include "../../../include/minishell.h"

// Need to skip some flags here!! -n -n -n should work as well
int	b_echo(int argc, char **argv, char **envp, t_shell *shell)
{
	int		i;
	bool	new_line;

	(void)envp;
	(void)shell;
	i = 1;
	new_line = true;
	if (argc > 1 && ft_strncmp(argv[1], "-n", ft_strlen(argv[1])) == 0)
	{
		new_line = false;
		i++;
	}
	while (i < argc)
	{
		if (ft_strncmp(argv[i], "-n", ft_strlen(argv[i])) != 0)
		{
			printf("%s", argv[i]);
			if (i + 1 < argc)
				printf(" ");
		}
		i++;
	}
	if (new_line == true)
		printf("\n");
	return (0);
}
