
#include "../../include/minishell.h"

void	free_t_tasks(void *ptr)
{
	t_task	*task;

	task = (t_task *)ptr;
	ft_list_semi_clear(&task->tokens);
	ft_lstclear(&task->pipes, free_t_pipe);
	free(task->tokens);
	free(task);
}

void	add_task(t_shell *shell, t_task *task, t_token_type type, int index)
{
	task->type = type;
	task->index = index;
	ft_lstadd_back(&shell->tasks, ft_lstnew(task));
}

static bool	in_list(int token, int *list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		if (list[i] == token)
			return (true);
		i++;
	}
	return (false);
}

void	break_tasks(t_shell *shell)
{
	t_list		*token;
	t_task		*task;
	int			index;

	index = 0;
	token = shell->tokens;
	if (!token)
		return ;
	task = mem_add(1, sizeof(t_task));
	while (token)
	{
		if (in_list(((t_token *)token->content)->token,
				(int []){AND_IF, OR_IF, SEMICOLON, 0}))
		{
			add_task(shell, task, ((t_token *)token->content)->token, index++);
			task = mem_add(1, sizeof(t_task));
		}
		else
			ft_lstadd_back(&task->tokens, ft_lstnew(token->content));
		token = token->next;
	}
	add_task(shell, task, WORD, index++);
}
