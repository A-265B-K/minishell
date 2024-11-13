
#include "../../include/minishell.h"

static bool	file_in_dir(char *searchpath, char *filename)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(searchpath);
	if (!dir)
		return (false);
	entry = readdir(dir);
	while (entry)
	{
		if (ft_strcmp(entry->d_name, filename) == 0)
		{
			closedir(dir);
			return (true);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (false);
}

char	*file_searchpath(char *filename, char *envp[])
{
	char	**searchpath;

	searchpath = env_get_searchpaths(envp);
	while (*searchpath)
	{
		if (file_in_dir(*searchpath, filename))
			return (*searchpath);
		searchpath++;
	}
	return (NULL);
}
