/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/04 15:03:03 by alkuijte      #+#    #+#                 */
/*   Updated: 2024/11/04 17:45:09 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

t_token	*new_node(char *str)
{
	t_token	*node;

	node = ft_calloc(1, sizeof(t_token));
	if (!node)
		return (NULL);
	node->data = str;
	node->next = NULL;
	return (node);

	// ? asign the values immediately or init to NULL and 0s?
}

void	add_to_back(t_token *node, char *str)
{
	if (node == NULL)
	{
		node = new_node(str);
		return ;
	}
	while (node->next)
		node = node->next;
	node->next = new_node(str);
}