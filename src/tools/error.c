
#include "../../include/minishell.h"

/**
 * @brief Prints the optional string and the errno message to STDERR_FILENO.
 * @param str optional string
 * @return int errno or EXIT_FAILURE
 */
int	error(char *str)
{
	if (errno != 0)
	{
		if (str)
			perror(str);
		else
			perror("Error");
		return (errno);
	}
	if (str)
	{
		ft_putstr_fd("Error: ", STDERR_FILENO);
		ft_putendl_fd(str, STDERR_FILENO);
	}
	else
		ft_putendl_fd(ERR_UNKOWN, STDERR_FILENO);
	return (EXIT_FAILURE);
}
