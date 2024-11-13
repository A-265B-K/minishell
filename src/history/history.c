
#include "../../include/minishell.h"

void	history_add(char *line, t_shell *shell)
{
	if (ft_strlen(line) == 0)
		return ;
	if ((shell->history_entry == NULL || shell->history_state == NULL)
		|| ft_strcmp(shell
			->history_entry[shell->history_state->length - 1]->line, line) != 0)
		add_history(line);
	if (EXTRA)
		write_history(".history");
}

void	history_init(t_shell *shell)
{
	shell->history_entry = history_list();
	shell->history_state = history_get_history_state();
	if (EXTRA)
	{
		if (read_history(".history"))
			if (write_history(".history"))
				error(ERR_HISTORY);
		using_history();
		debug("History enabled");
	}
}
