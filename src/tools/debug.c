
#include "../../include/minishell.h"

static char	*ident(int depth, int is_last, int extra)
{
	int	i;

	i = 0;
	while (i < depth)
	{
		if (extra > -1 && i == extra)
			printf("│    ");
		else if (i < depth - 1)
			printf("     ");
		if (i == depth - 1)
		{
			if (is_last)
				return ("└── ");
			else
				return ("├── ");
		}
		i++;
	}
	return ("");
}

static void	print_pipes(t_list *pipes, int level, int is_last, int extra)
{
	int		i;
	int		x;
	t_pipe	*pipe;

	i = 0;
	x = 0;

	if (pipes != NULL)
	{
		while (pipes)
		{
			pipe = pipes->content;
			is_last = pipes->next == NULL;
			printf("%s%s %d : Argc: %d:\n", ident(level + 1, is_last, extra), "pipe", i, pipe->argc);
			x = 0;
			while (x < pipe->argc)
			{
				if (pipe->argc - x == 0)
					is_last = 1;
				if (!is_last)
					extra = level - 1;
				else
					extra = -1;
				printf("%s>%s<\n", ident(level + 2, is_last, extra), pipe->argv[x]);
				x++;
			}
			pipes = pipes->next;
			i++;
		}
	}
}

static void	print_task(t_task *task, int level, int is_last)
{
	int		extra;
	int		i;

	i = 0;
	if (task != NULL)
	{
		if (!is_last)
			extra = level - 1;
		else
			extra = -1;
		printf("%sid: %d\n", ident(level + 1, 0, extra), task->index);
		if (task->pipes->next == NULL)
			is_last = 1;
		else
			is_last = 0;
		printf("%spipe count: %d\n", ident(level + 1, 1, extra), ft_lstsize(task->pipes));
		print_pipes(task->pipes, level + 1, is_last, extra);
		i++;
	}
}

void	print_tasks(t_list *tasks)
{
	t_task	*task;
	int		last;

	while (tasks)
	{
		if (tasks->next == NULL)
			last = 1;
		else
			last = 0;
		task = tasks->content;
		printf("%s%s%d : %p:\n", ident(2, last, -1), "tasks ", task->index, task);
		print_task(task, 2, last);
		tasks = tasks->next;
	}
}

void	print_shell(t_shell *s)
{
	if (s != NULL)
	{
		printf("%s%s\n", ident(0, 0, -1), "shell");
		printf("%s%s%s\n", ident(1, 0, -1), "prompt: ", s->prompt);
		printf("%s%s%d\n", ident(1, 0, -1), "debug: ", s->debug);
		printf("%s%s%s\n", ident(1, 0, -1), "raw_input: ", s->input);
		printf("%s%s%d\n", ident(1, 0, -1), "exitcode: ", s->exitcode);
		printf("%s%s\n", ident(1, 1, -1), "tasks: ");

		print_tasks(s->tasks);
		printf("\n%s", NORMAL);
	}
}

/**
 * @brief Prints a string (in YELLOW)
 * with prefix 'Debug'.
 * 
 * @param str 
 */
void	debug(char *str)
{
	if (DEBUG == true)
		printf("%sDebug: %s%s\n", YELLOW, str, NORMAL);
}
