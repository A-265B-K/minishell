/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebayat <ebayat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:26:42 by ebayat            #+#    #+#             */
/*   Updated: 2024/09/23 15:40:00 by ebayat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"




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