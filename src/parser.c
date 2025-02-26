/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/20 12:41:34 by ahornstr      #+#    #+#                 */
/*   Updated: 2025/02/26 16:31:25 by alkuijte      ########   odam.nl         */
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


int identify_builtin(t_commands *command, t_token *current)
{

    if (ft_strncmp(current->str, "echo", 4) == 0 || ft_strncmp(current->str, "cd", 2) == 0 || ft_strncmp(current->str, "pwd", 3) == 0)
	{
		if (!command->builtin)
		{
        	command->builtin = ft_strdup(current->str);
			return (1);
		}
	}
	if (ft_strncmp(current->str, "export", 6) == 0 || ft_strncmp(current->str, "unset", 5) == 0 || ft_strncmp(current->str, "exit", 4) == 0)
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
        if (!identify_builtin(current_command, current_token))
        {
            current_command->str = realloc(current_command->str, sizeof(char *) * (arg_count + 2));
            current_command->str[arg_count] = ft_strdup(current_token->str);
            current_command->str[arg_count + 1] = NULL;
            arg_count++;
        }
    }
	return (arg_count);
}

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

// void	get_env_var(t_shell *shell, t_commands *com_struct)
// {
// 	char	*buffer;
// 	int	i;
	
// 	buffer = NULL;
// 	i = 0;
// 	while (com_struct)
//     {
// 		if (com_struct->str)
// 		{
// 			while (com_struct->str[i])
// 			{
// 				if (com_struct->str[i][0] == '$')
// 				{
// 					buffer = ft_substr(com_struct->str[i], 1, ft_strlen(com_struct->str[i]));
// 					if (search_env(shell->envp, buffer))
// 					{
// 						free (com_struct->str[i]);
// 							com_struct->str[i] = ft_strdup(search_env(shell->envp, buffer));
// 						if (!com_struct->str[i])
// 							perror("malloc get_env_var --> substr return");
// 					}
// 					if (buffer)
// 					free (buffer);
// 				}
// 				i++;
// 			}
// 		}
// 		com_struct = com_struct->next;
//     }
// 	while (com_struct)
// 	{
// 		com_struct = com_struct->prev;
// 	}
// }

char *expand_env_var(const char *var)
{
    char *value;

	value = getenv(var);
    if (!value)
        return (ft_strdup(""));
    return (ft_strdup(value));
}

static void toggle_quotes(char c, int *in_single, int *in_double)
{
    if (c == '\'' && !(*in_double))
		*in_single = !(*in_single);
    else if (c == '"' && !(*in_single))
		*in_double = !(*in_double);
}

int	handle_exitcode(char **result, char *expand, int *j, int *i, t_shell *shell)
{
	expand = ft_itoa(shell->exitcode);
	if (!expand)
		return (0);
	int new_size = ft_strlen(*result) + ft_strlen(expand) + 1;
	*result = realloc(*result, new_size);
	if (!*result)
	{
		free(expand);
		return (0);
	}
	memcpy(&(*result)[*j], expand, ft_strlen(expand));
	*j += ft_strlen(expand);
	free(expand);
	*i += 1;
	return (1);
}
static int handle_variable_expansion(const char *input, int *i, char **result, int *j, t_shell *shell)
{
    char	*var_name;
    char	*expand;
    int		start;
    int		len;

	expand = NULL;
	if (input[*i + 1] == '?')
		return (handle_exitcode(result, expand, i, j, shell));
    start = *i + 1;
    while (ft_isalnum(input[start]) || input[start] == '_')
        start++;
    len = start - (*i + 1);
    if (len <= 0)
        return (0);
    var_name = malloc(len + 1);
    if (!var_name)
        return (0);
    ft_strlcpy(var_name, &input[*i + 1], len + 1);
    expand = expand_env_var(var_name);
    free(var_name);
    if (expand)
    {
        int new_size = ft_strlen(*result) + ft_strlen(expand) + 1;
        *result = realloc(*result, new_size);
        if (!*result)
        {
            free(expand);
            return (0);
        }
        memcpy(&(*result)[*j], expand, ft_strlen(expand));
        *j += ft_strlen(expand);
        free(expand);
    }
    *i += len;
    return (1);
}


char *remove_quotes(const char *input, t_shell *shell)
{
    int i = 0;
	int	j = 0;
	int in_single = 0;
	int in_double = 0;
    char *result;
	
	result = malloc(ft_strlen(input) + 1);
    if (!result)
		return NULL;
    while (input[i])
	{
        toggle_quotes(input[i], &in_single, &in_double);
        if (input[i] == '$' && !in_single)
		{
            if (handle_variable_expansion(input, &i, &result, &j, shell))
				break ;
		}
        else if (!(input[i] == '\'' && !in_double) && !(input[i] == '"' && !in_single))
            result[j++] = input[i];
        i++;
    }
	result[j] = '\0';
    return (result);
}

void process_quotes_in_commands(t_commands *cmd, t_shell *shell)
{
	int	i;
	char *temp;
	char *temp_b;

	i = 0;
	temp = NULL;
    while (cmd)
	{
		if (cmd->builtin)
		{
			temp = remove_quotes(cmd->builtin, shell);
			free(cmd->builtin);
			cmd->builtin = temp;
		}
		i = 0;
		while (cmd->str && cmd->str[i])
		{
			temp_b = remove_quotes(cmd->str[i], shell);
			free(cmd->str[i]);
			cmd->str[i] = temp_b;
			i++;
		}
        cmd = cmd->next;
    }
}

void	parser(t_shell	*shell)
{
	if(!syntax_check(shell))
	{
	//	printf("SYNTAX VALID\n");
	}
	else
		return ;
	shell->com_struct = parse_tokens(shell->lexer_grouped);
	process_quotes_in_commands(shell->com_struct, shell);
	//print_parser(shell->com_struct);
	
}