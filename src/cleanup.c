/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ahornstr <ahornstr@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/10 16:36:38 by ahornstr      #+#    #+#                 */
/*   Updated: 2025/02/11 17:19:47 by wdpk          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_up_parser(t_shell *shell)
{
	if (shell)
	{
		while (shell->tokenized)
		{
			if (shell->tokenized->str)
				free(shell->tokenized->str);
			shell->tokenized->prev = NULL;
			shell->tokenized = shell->tokenized->next;
		}
		free (shell->tokenized);
	}
}

