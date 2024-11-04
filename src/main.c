/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ebayat <ebayat@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/24 12:12:05 by ebayat        #+#    #+#                 */
/*   Updated: 2024/11/04 17:17:40 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	init_program(t_program *program_data, char **envp)
{
	program_data->prompt_symbol = " $ ";
	program_data->envp = envp;
	program_data->user_input = NULL;
	program_data->tokens = NULL;
	program_data->fd_in = dup(STDIN_FILENO);
	program_data->fd_out = dup(STDOUT_FILENO);
}

void run_program(t_program *program_data)
{
	while(1) // ? why is this a while(1)?
	{
		// check_for_signal_of_parent();
		get_user_input(program_data);
		process_input(program_data);
		execute_command(program_data);
		while(program_data->tokens)
		{
			printf("[%s]\n", program_data->tokens->data);
			program_data->tokens = program_data->tokens->next;
		}
		// free_everything_for_the_next_input();
		minishell_exit(program_data);
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_program program_data;

	init_program(&program_data, envp);
	run_program(&program_data);
	
	minishell_exit(&program_data);
}