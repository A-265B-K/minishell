/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahornstr <ahornstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:52:23 by alkuijte          #+#    #+#             */
/*   Updated: 2024/12/02 13:13:49 by ahornstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	envp = NULL;
	argv = NULL;
	argc = 0;
	char* buf;
	t_shell *tstruct;

	tstruct = malloc(sizeof(t_shell));
	tstruct->exitcode = 0;
	disable_std_behaviour();
	signal_handling(1);
	while ((buf = readline("Shell_template: ")) != NULL)
	{
		if (strlen(buf) > 0) 
		{
//			printf("%s\n", buf);
			add_history(buf);
			function_call(1, buf, tstruct);
		}
		free(buf);
	}
}
