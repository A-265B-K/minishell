/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebayat <ebayat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:53:38 by ebayat            #+#    #+#             */
/*   Updated: 2024/08/08 11:59:23 by ebayat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	minishell_exit(t_program *program_data);

void	minishell_exit(t_program *program_data)
{
	// free(program_data->user_input);
	// program_data->user_input = NULL;
	(void)program_data;
	printf(">>> EXITING\n");
	exit(errno);
}

// void	minishell_free_all(t_program *program_data)
// {
// 	// free prompt_symbol
// 	// free user_input
// 	// free tokens
// }