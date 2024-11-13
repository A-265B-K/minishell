
#include "../../include/minishell.h"

void	free_t_token(void *token)
{
	t_token	*tmp;

	tmp = (t_token *)token;
	free(tmp->raw);
	free(tmp->value);
	free(tmp);
}

/**
 * @brief If the current character is a '#', it and all subsequent characters
 * up to, but excluding, the next <newline> shall be discarded as a comment.
 * The <newline> that ends the line is not considered part of the comment.
 * 
 * @param str 
 * @param list 
 * @return int 
 */
static int	get_comment(const char *str, t_list **list)
{
	t_token	*token;
	int		i;

	i = 0;
	if (str[0] && str[0] == '#')
	{
		while (str[i] && str[i] != '\n')
			i++;
		debug("Comment found");
		token = mem_add(1, sizeof(t_token));
		token->value = ft_substr(str, 0, i);
		token->token = COMMENT;
		ft_lstadd_back(list, ft_lstnew(token));
		return (i);
	}
	return (0);
}

/**
 * @brief  If the current character is an unquoted <blank>,
 * any token containing the previous character is delimited
 * and the current character shall be discarded.
 * 
 * @param str 
 * @return int 
 */
static int	get_blank(const char *str, t_list **list)
{
	t_token	*token;
	int		i;

	i = 0;
	if (str[0] && str[0] == ' ')
	{
		while (str[i] && str[i] == ' ')
			i++;
		debug("Blank found");
		token = mem_add(1, sizeof(t_token));
		token->value = ft_substr(str, 0, i);
		token->token = ' ';
		ft_lstadd_back(list, ft_lstnew(token));
		return (i);
	}
	return (0);
}

/**
 * @brief The shell shall read its input in terms of lines.
 * The input lines can be of unlimited length.
 * These lines shall be parsed using two major modes:
 * ordinary token recognition and processing of here-documents.
 * 
 * When an io_here token has been recognized by the grammar,
 * one or more of the subsequent lines immediately following
 * the next NEWLINE token form the body of one or more here-documents
 * and shall be parsed according to the rules of Here-Document. 
 * 
 * When it is not processing an io_here, the shell shall break its input
 * into tokens by applying the first applicable rule below to the next 
 * character in its input.
 * 
 * The token shall be from the current position in the input
 * until a token is delimited according to one of the rules below; 
 * the characters forming the token are exactly those in the input, 
 * including any quoting characters. If it is indicated that a token
 * is delimited, and no characters have been included in a token,
 * processing shall continue until an actual token is delimited.
 * 
 * Once a token is delimited,
 * it is categorized as required by the grammar in Shell Grammar.
 * 
 * @param shell 
 */
void	tokenizer(t_shell *shell)
{
	int			i;

	i = 0;
	while (shell->input[i])
	{
		i += get_double_operator(&shell->input[i], &shell->tokens);
		i += get_single_operator(&shell->input[i], &shell->tokens);
		i += get_quote(&shell->input[i], &shell->tokens);
		i += get_param(&shell->input[i], &shell->tokens);
		i += get_word(&shell->input[i], &shell->tokens);
		i += get_blank(&shell->input[i], &shell->tokens);
		i += get_comment(&shell->input[i], &shell->tokens);
	}
}
