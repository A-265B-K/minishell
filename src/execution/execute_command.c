/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_command.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ebayat <ebayat@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/26 14:26:42 by ebayat        #+#    #+#                 */
/*   Updated: 2024/10/20 16:51:46 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"




void	execute_command(t_program *program_data)
{
	// const char *command = "ls";
	// execve("/bin/ls", command, program_data->envp);
	(void)(program_data);
	printf(">>> EXECUTED COMMANDS\n");
}
void	execute_commands()
{
	// go through tokens and groups them according to concurrency (so &, and |, should happen concurrently, &&, ;, should happen asynced)
	//	 execute



}

// TEST
// int	main(int argc, char **argv, char **envp)
// {
// 	execve("/bin/ls", &argv[1], envp);
// }