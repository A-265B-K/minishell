
#include "../../include/minishell.h"

void	free_t_pipe(void *ptr)
{
	t_pipe	*pipe;

	pipe = (t_pipe *)ptr;
	ft_list_semi_clear(&pipe->tokens);
	free(pipe->tokens);
	free_double(pipe->argv);
	free(pipe);
}

void	break_pipes(t_task *task)
{
	t_list		*tokens;
	t_pipe		*pipe;
	int			index;

	index = 0;
	tokens = task->tokens;
	pipe = mem_add(1, sizeof(t_pipe));
	while (tokens)
	{
		if (((t_token *)tokens->content)->token == '|' 
		|| ((t_token *)tokens->content)->token == '>'
		|| ((t_token *)tokens->content)->token == DGREAT
		|| ((t_token *)tokens->content)->token == '<'
		)
		{
			pipe->index = index++;
			ft_lstadd_back(&task->pipes, ft_lstnew(pipe));
			pipe = mem_add(1, sizeof(t_pipe));
		}
		else
			ft_lstadd_back(&pipe->tokens, ft_lstnew(tokens->content));
		tokens = tokens->next;
	}
	pipe->index = index++;
	ft_lstadd_back(&task->pipes, ft_lstnew(pipe));
}
