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

#include "../incl/minishell.h"

// while(tokens)
//	if (is_redirect)
//		get the operator token
//		get redirect destination from token->next 
//		adapt node redication to node that would be redirected