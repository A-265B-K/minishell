/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebayat <ebayat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:42:31 by ebayat            #+#    #+#             */
/*   Updated: 2024/08/02 15:40:26 by ebayat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	process_input(t_program *program);
void	tokenize(t_program *program);

void	process_input(t_program *program)
{
	tokenize(program);
	// perform_shell_expansions(program);
	// deal with redirects
	printf(">>> Command processed\n");
}

