/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_user_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebayat <ebayat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:26:42 by ebayat            #+#    #+#             */
/*   Updated: 2024/07/29 13:43:51 by ebayat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"



void get_user_input(t_program *program_data)
{
	program_data->tokens = new_node(readline(program_data->prompt_symbol));
	add_history(program_data->tokens->data);

	
	// ? bonus maybe: save whatever is being typed (even if user hasn't pressed enter) and have an easy way to clean/reset the line
	// ? Does it matter if the prompt is displayed through readline or manually printed?
	// ? Does history require additional steps?bas
	// ? Are there any other places where the prompt symbol is used? If not, it'd be unnecessary to have it declared and assigned in a struct.

}