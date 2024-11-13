
#include "../../include/minishell.h"

void	parser(t_shell *shell)
{
	t_list		*task;

	break_tasks(shell);
	task = shell->tasks;
	while (task)
	{
		break_pipes(task->content);
		task = task->next;
	}
}
