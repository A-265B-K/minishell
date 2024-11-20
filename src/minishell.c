/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahornstr <ahornstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:52:23 by alkuijte          #+#    #+#             */
/*   Updated: 2024/11/20 16:52:55 by ahornstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	envp = NULL;
	argv = NULL;
	argc = 0;
	char* buf;
	while ((buf = readline("Shell_template: ")) != NULL) {
    if (strlen(buf) > 0) 
      add_history(buf);
    free(buf);
  }
}