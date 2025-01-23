/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahornstr <ahornstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:36:38 by ahornstr          #+#    #+#             */
/*   Updated: 2025/01/23 19:38:52 by ahornstr         ###   ########.fr       */
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
		free (shell->tokenized)
	}
}