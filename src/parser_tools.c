
#include "minishell.h"

t_commands *create_command_node(int count)
{
    t_commands *new_command;
    
    new_command = malloc(sizeof(t_commands));
    if (!new_command)
		return NULL;
	new_command->id = count;
    new_command->str = NULL;
    new_command->builtin = NULL;
    new_command->tokenized = NULL;
    new_command->redirection = NULL;
    new_command->next = NULL;
    new_command->prev = NULL;
    return (new_command);
}

void add_command_to_list(t_commands **commands, t_commands *new_command)
{
    t_commands *last;

    last = NULL;
    if (*commands == NULL)
        *commands = new_command;
    else
    {
       last = *commands;
        while (last->next)
            last = last->next;
        last->next = new_command;
        new_command->prev = last;
    }
}
