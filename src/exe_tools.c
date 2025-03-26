/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:11:16 by marvin            #+#    #+#             */
/*   Updated: 2025/03/23 14:11:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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