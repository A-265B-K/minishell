
#include "../../include/minishell.h"

/**
 * @brief If the current character is not quoted
 * and can be used as the first character of a new operator,
 * the current token (if any) shall be delimited.
 * 
 * The current character shall be used as the beginning
 * of the next (operator) token.
 * 
 * If the previous character was part of a word,
 * the current character shall be appended to that word.
 * 
 * @param str 
 * @param list 
 * @return int 
 */
int	get_word(const char *str, t_list **list)
{
	t_token	*token;
	int		x;

	x = 0;
	if (!is_quote(str) && !is_operator(str[0]))
	{
		while (str[x] && str[x] != ' ' && str[x] != '#' && !is_operator(str[x]))
			x++;
		if (x == 0)
			return (0);
		debug("Word found");
		token = mem_add(1, sizeof(t_token));
		token->value = ft_substr(str, 0, x);
		token->token = WORD;
		ft_lstadd_back(list, ft_lstnew(token));
		return (x);
	}
	return (0);
}
