/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution_misc.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/05 18:07:52 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/03/09 12:52:27 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_dir(const char *file_path)
{
	struct stat	path_stat;

	if (!stat(file_path, &path_stat))
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

int	error_handler(char *str, int exitcode)
{
	dprintf(2, "%s\n", str);
	return (exitcode);
}

// void	debug_fds(const char *msg)
// {
// 	printf("%s\n", msg);
// 	for (int fd = 0; fd < 10; fd++)
// 	{
// 		if (fcntl(fd, F_GETFD) != -1)
// 			dprintf(2, "FD %d is open\n", fd);
// 	}
// }