#include "minishell.h"

// syntax check not done, need to add:
// -- redirection operator errors --> >    > for example [DONE]
// -- Quotes! what to do with them? error message or no? well now we know
// •Handle ’ (single quote) which should prevent the shell from interpreting the meta-
// characters in the quoted sequence.
// •Handle " (double quote) which should prevent the shell from interpreting the meta-
// characters in the quoted sequence except for $ (dollar sign).

int	syntax_check(t_shell *shell)
{
	if (!operator_placement(shell))
	{
		//printf("Operators place correct\n");
	}
	else
		return (42);
	return (0);
}



// int	builtin_count(t_shell *shell)
// {
// 	t_token *temp;
// 	temp = shell->lexer_grouped;
// 	int	count;

// 	count = 0;
// 	while (temp->id != 0)
// 	{
// 		temp = temp->prev;
// 	}
// 	while (temp && temp->next)
// 	{
// 		while (temp->str)
// 	}

// }

int	operator_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_operator(str[i]))
		{
			while (isspace(str[i]))
			{
				i++;
				if (is_operator(str[i]))
					return (0);
			}
		}
		i++;
	}
	return (1);
}

int unclosed_quotes(const char *input)
{
    char open_quote;
    int i;

    i = 0;
    open_quote = '\0';
    while (input[i])
    {
        if (input[i] == '\'' || input[i] == '"')
        {
            if (open_quote == '\0')
                open_quote = input[i];
            else if (open_quote == input[i])
                open_quote = '\0';
        }
        i++;
    }
    if (open_quote != '\0')
        return (0);
    return (1);
}

int	operator_placement(t_shell *shell)
{
	t_token	*temp;
	if (shell->tokenized)
		temp = shell->tokenized;
	else
		return (0);
	while (temp && temp->id != 0)
	{
		temp = temp->prev;
	}
	if (!operator_check(shell->input))
		error("syntax error near unexpected token");
	while (temp)
	{
		if (is_operator(temp->c))
		{
			if ((is_operator(temp->c) && !temp->next) || (is_operator(temp->c) && temp->id == 0))
			{
				error("syntax error near unexpected token\n");
				return (1);
			}
		}
		temp = temp->next;
	}
	return (0);
}
