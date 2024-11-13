
#include "../../include/minishell.h"

/**
 * @brief Return stringlength of quote if the current character is a quote.
 * 
 * @param str 
 * @return int 
 */
int	is_quote(const char *str)
{
	int		i;

	i = 0;
	if (str[0] == '"' || str[0] == '\'')
	{
		i++;
		while (str && str[i])
		{
			if (str[i] == str[0])
				return (i + 1);
			i++;
		}
	}
	return (0);
}

/**
 * @brief If the current character is <backslash>, single-quote,
 * or double-quote and it is not quoted, it shall affect quoting
 * for subsequent characters up to the end of the quoted text.
 * 
 * The rules for quoting are as described in Quoting.
 * 
 * During token recognition no substitutions shall be actually performed,
 * and the result token shall contain exactly the characters that appear
 * in the input (except for <newline> joining), unmodified,
 * including any embedded or enclosing quotes or substitution operators,
 * between the <quotation-mark> and the end of the quoted text.
 * 
 * The token shall not be delimited by the end of the quoted field.
 * 
 * @param i 
 * @param start 
 * @param str 
 * @param list 
 */
int	get_quote(const char *str, t_list **list)
{
	t_token	*token;

	if (is_quote(str))
	{
		debug("Quote found");
		token = mem_add(1, sizeof(t_token));
		token->value = ft_substr(str, 0, is_quote(str));
		token->token = PARAMETER;
		ft_lstadd_back(list, ft_lstnew(token));
		return (is_quote(str));
	}
	return (0);
}
