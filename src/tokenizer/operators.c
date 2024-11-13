
#include "../../include/minishell.h"

static t_token_type	get_double_operator_meta(char *str)
{
	if (ft_strncmp(str, "<<", 2) == 0)
		return (DLESS);
	if (ft_strncmp(str, ">>", 2) == 0)
		return (DGREAT);
	if (ft_strncmp(str, "&&", 2) == 0)
		return (AND_IF);
	if (ft_strncmp(str, "||", 2) == 0)
		return (OR_IF);
	if (ft_strncmp(str, ";;", 2) == 0)
		return (DSEMI);
	if (ft_strncmp(str, "<&", 2) == 0)
		return (LESSAND);
	if (ft_strncmp(str, ">&", 2) == 0)
		return (GREATAND);
	if (ft_strncmp(str, "<>", 2) == 0)
		return (LESSGREAT);
	if (ft_strncmp(str, "<<-", 3) == 0)
		return (DLESSDASH);
	if (ft_strncmp(str, ">|", 2) == 0)
		return (CLOBBER);
	return (WORD);
}

int	is_operator(char c)
{
	if (c == '|' || c == ';' || c == '<' || c == '>' || c == '&')
		return (true);
	return (false);
}

/**
 * @brief If the previous character was used as part of an operator
 * and the current character is not quoted
 * and can be used with the previous characters to form an operator,
 * it shall be used as part of that (operator) token.
 * 
 * @param i 
 * @param start 
 * @param str 
 * @param list 
 * @return true 
 * @return false 
 */
int	get_double_operator(const char *str, t_list **list)
{
	t_token	*part;

	if (!is_quote(str)
		&& is_operator(str[0])
		&& is_operator(str[1]))
	{
		debug("Double operator found");
		part = mem_add(1, sizeof(t_token));
		part->value = ft_substr(&str[0], 0, 2);
		part->token = get_double_operator_meta(part->value);
		ft_lstadd_back(list, ft_lstnew(part));
		return (2);
	}
	return (0);
}

/**
 * @brief If the previous character was used as part of an operator
 * and the current character cannot be used
 * with the previous characters to form an operator, 
 * the operator containing the previous character shall be delimited.
 * 
 * @param i 
 * @param start 
 * @param str 
 * @param list 
 * @return true 
 * @return false 
 */
int	get_single_operator(const char *str, t_list **list)
{
	t_token	*token;

	if (!is_quote(str)
		&& is_operator(str[0])
		&& (str[1] && !is_operator(str[1])))
	{
		debug("Single operator found");
		token = mem_add(1, sizeof(t_token));
		token->value = ft_substr(str, 0, 1);
		token->token = token->value[0];
		ft_lstadd_back(list, ft_lstnew(token));
		return (1);
	}
	return (0);
}
