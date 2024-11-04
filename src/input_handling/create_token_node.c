/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_token_node.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: ebayat <ebayat@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/26 14:26:42 by ebayat        #+#    #+#                 */
/*   Updated: 2024/10/20 16:51:57 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

t_token	*new_node(char *str)
{
	t_token	*node;

	node = ft_calloc(1, sizeof(t_token));
	if (!node)
		return (NULL);
	node->command = str;
	node->next = NULL;
	return (node);

	// ? asign the values immediately or init to NULL and 0s?
}