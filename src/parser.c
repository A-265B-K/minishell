/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahornstr <ahornstr@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/20 12:41:34 by ahornstr      #+#    #+#                 */
/*   Updated: 2025/01/27 16:14:26 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void handle_redirection(t_commands *command, t_token *current)
{
    if (current->token == O_LESS || current->token == O_GREAT || current->token == O_DLESS || current->token == O_DGREAT)
    {
        command->redirection = ft_strjoin(current->str, current->next->str);
        current = current->next->next;
    }
}

void free_command_node(t_commands *command)
{
	int i;

	i = 0;
    if (!command)
		return;
	while(command && command->id != 0)
	{
		command = command->prev;
	}
	while (command && command->next)
	{
   		if (command->str)
    	{
        	while (command->str[i])
			{
				free(command->str[i]);
				i++;
			}
		}
        free(command->str);
		if (command->redirection)
			free(command->redirection);
    	if (command->builtin)
			free(command->builtin);
		command = command->next;
    }
    free(command);
}

// this can be written cleaner.

int identify_builtin(t_commands *command, t_token *current)
{
    if (ft_strncmp(current->str, "echo", 4) == 0 || ft_strncmp(current->str, "cd", 2) == 0 || ft_strncmp(current->str, "pwd", 3) == 0)
	{
        command->builtin = ft_strdup(current->str);
		return (1);
	}
	if (ft_strncmp(current->str, "export", 6) == 0 || ft_strncmp(current->str, "unset", 5) == 0 || ft_strncmp(current->str, "exit", 4) == 0)
	{
        command->builtin = ft_strdup(current->str);
		return (1);
	}
	return (0);
}

// shorten please!
t_commands *parse_tokens(t_token *lexer_grouped)
{
    t_commands *commands = NULL;
    t_commands *current_command = create_command_node(0);
    t_token *current_token = lexer_grouped;
    int arg_count = 0;
    int node_count = 0;

    while (current_token)
    {
        if (current_token->token == O_LESS || current_token->token == O_GREAT || 
            current_token->token == O_DLESS || current_token->token == O_DGREAT)
        {
            handle_redirection(current_command, current_token);
			current_token = current_token->next;
        }
        else if (current_token->token == O_G_WORD)
        {
            if (!identify_builtin(current_command, current_token))
            {
                current_command->str = realloc(current_command->str, sizeof(char *) * (arg_count + 2));
                current_command->str[arg_count] = ft_strdup(current_token->str);
                current_command->str[arg_count + 1] = NULL;
                arg_count++;
            }
        }
        else if (current_token->token == O_PIPE)
        {
            add_command_to_list(&commands, current_command);
            node_count++;
            current_command = create_command_node(node_count);
            arg_count = 0;
		}
        current_token = current_token->next;
    }
    if (current_command->str || current_command->redirection || current_command->builtin)
        add_command_to_list(&commands, current_command);
    else
        free_command_node(current_command);
    return (commands);
}

void	print_parser(t_commands *commands)
{
    int command_index = 1;

    while (commands)
    {
        printf("Command %d:\n", command_index++);
        if (commands->str)
        {
            printf("  Arguments: ");
            for (int i = 0; commands->str[i] != NULL; i++)
            {
                printf("[%s] ", commands->str[i]);
            }
            printf("\n");
        }
        else
            printf("  Arguments: None\n");
        if (commands->builtin)
            printf("  Builtin: %s\n", commands->builtin);
        else
            printf("  Builtin: None\n");
        if (commands->redirection)
            printf("  Redirection: %s\n", commands->redirection);
        else
            printf("  Redirection: None\n");
        commands = commands->next;
    }
}

// to do parser
// Environment variables, pretty easy leave till last maybe
// heredoc support
// add more syntax checks
// builtin flags manually?
// error handling for the whole project.

void	parser(t_shell	*shell)
{
	if(!syntax_check(shell))
	{
	//	printf("SYNTAX VALID\n");
	}
	shell->com_struct = parse_tokens(shell->lexer_grouped);
	// print_parser(shell->com_struct);
	
}