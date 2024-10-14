/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudo_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebayat <ebayat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:12:05 by ebayat            #+#    #+#             */
/*   Updated: 2024/08/02 15:42:14 by ebayat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

main(int argc, char **argv, char **envp)
{
	(void)argv;
	t_program program_data;

	init_program();
	run_program();
}

run_program()
{
	while(1)
	{
		check_for_signal_of_parent();
		get_command();
		process_input();
		execute_commandS();
		free_everything_for_the_next_input();
	}
}


init_program()
{
	
}



process_input()
{
	seperate_commands_into_tokens();
	parse_tokens();
	perform_shell_expansions();
}

get_command()
{
	// The user can write in a command or use the history. Eitherway a prompt is displayed. 
	display_prompt();
	get_input();
	save_given_command_to_history();
	// ? bonus maybe: save whatever is being typed and have an easy way to clean/reset the line
}


perform_shell_expansions()
{
	expand_environemt_variables();
}


execute_commandS()
{
	do redirection stuff
	execve();
}