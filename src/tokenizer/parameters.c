
#include "../../include/minishell.h"

/**
 * @brief If the current character is an unquoted '$' or '`',
 * the shell shall identify the start of any candidates
 * for parameter expansion (Parameter Expansion),
 * command substitution (Command Substitution),
 * or arithmetic expansion (Arithmetic Expansion)
 * from their introductory unquoted character sequences: 
 * '$' or "${", "$(" or '`', and "$((", respectively.
 * 
 * The shell shall read sufficient input to determine
 * the end of the unit to be expanded (as explained in the cited sections).
 * 
 * While processing the characters, if instances of expansions
 * or quoting are found nested within the substitution,
 * the shell shall recursively process them in the manner specified
 * for the construct that is found.
 * 
 * The characters found from the beginning of the substitution to its end,
 * allowing for any recursion necessary to recognize embedded constructs,
 * shall be included unmodified in the result token,
 * including any embedded or enclosing substitution operators or quotes.
 * The token shall not be delimited by the end of the substitution.
 */
int	get_param(const char *str, t_list **list)
{
	t_token	*token;
	int		x;

	x = 0;
	if (!is_quote(str) && str[0] == '$')
	{
		x++;
		while (str[x] && str[x] != ' '
			&& str[x] != '\'' && str[x] != '"' && str[x] != '#')
			x++;
		debug("Param found");
		token = mem_add(1, sizeof(t_token));
		token->value = ft_substr(str, 0, x);
		token->token = str[0];
		ft_lstadd_back(list, ft_lstnew(token));
		return (x);
	}
	return (0);
}
