/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahornstr <ahornstr@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/20 12:41:34 by ahornstr      #+#    #+#                 */
/*   Updated: 2025/02/11 17:27:16 by wdpk          ########   odam.nl         */
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
	int	len;
	
	len = ft_strlen(current->str);
    if (ft_strncmp(current->str, "echo", len) == 0 || ft_strncmp(current->str, "cd", len) == 0 || ft_strncmp(current->str, "pwd", len) == 0)
	{
		if (!command->builtin)
		{
        	command->builtin = ft_strdup(current->str);
			return (1);
		}
	}
	if (ft_strncmp(current->str, "export", len) == 0 || ft_strncmp(current->str, "unset", len) == 0 || ft_strncmp(current->str, "exit", len) == 0)
	{
		if (!command->builtin)
		{
        	command->builtin = ft_strdup(current->str);
			return (1);
		}
	}
	return (0);
}

int	parse_pipe(t_commands **commands, t_commands **current_command, int node_count)
{
	add_command_to_list(commands, *current_command);
    node_count++;
    *current_command = create_command_node(node_count);
    return (node_count);
}

int	parse_builtin(t_token *current_token, t_commands *current_command, int arg_count)
{
	if (current_token->token == O_G_WORD)
    {
        if (!identify_builtin(current_command, current_token)) // handle multiple builtins < HERE > second, third etc. builtins == O_WORD
        {
            current_command->str = realloc(current_command->str, sizeof(char *) * (arg_count + 2));
            current_command->str[arg_count] = ft_strdup(current_token->str);
            current_command->str[arg_count + 1] = NULL;
            arg_count++;
        }
    }
	return (arg_count);
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
			arg_count = parse_builtin(current_token, current_command, arg_count);
        else if (current_token->token == O_PIPE)
		{
			node_count = parse_pipe(&commands, &current_command, node_count);
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

char	*search_env(char **env, char *target)
{
	int	i;
	int	len;
	int	e_len;
	i = 0;
	if (target)
		len = ft_strlen(target);
	else
		return (NULL);
	while (env[i])
	{
		if (!ft_strncmp(env[i], target, len))
		{
			e_len = ft_strlen(env[i]);
			return (ft_substr(env[i], len + 1, e_len - (len + 1)));
		}
		i++;
	}
	return (NULL);
	
}

// change to get_env and not the struct envp** --> after merge
void	get_env_var(t_shell *shell, t_commands *com_struct)
{
	char	*buffer;
	int	i;
	
	buffer = NULL;
	i = 0;
	while (com_struct)
    {
		if (com_struct->str)
		{
			while (com_struct->str[i])
			{
				if (com_struct->str[i][0] == '$')
				{
					buffer = ft_substr(com_struct->str[i], 1, ft_strlen(com_struct->str[i]));
					if (search_env(shell->envp, buffer))
					{
						free (com_struct->str[i]);
							com_struct->str[i] = ft_strdup(search_env(shell->envp, buffer));
						if (!com_struct->str[i])
							perror("malloc get_env_var --> substr return");
					}
					if (buffer)
					free (buffer);
				}
				i++;
			}
		}
		com_struct = com_struct->next;
    }
	while (com_struct)
	{
		com_struct = com_struct->prev;
	}
}

// to do parser
// heredoc support
// add more syntax checks

// error handling for the whole project.
// Check if all quotes work !

void	parser(t_shell	*shell)
{
	if(!syntax_check(shell))
	{
	//	printf("SYNTAX VALID\n");
	}
	else
		return ;
	shell->com_struct = parse_tokens(shell->lexer_grouped);
	get_env_var(shell, shell->com_struct);
//	print_parser(shell->com_struct);
	
}