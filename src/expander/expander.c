
#include "../../include/minishell.h"

static void	strip_quoted(char **ptr)
{
	char	*new;
	char	*arg;

	arg = *ptr;
	if (arg && (arg[0] == '\'' || arg[0] == '\"'))
	{
		if (arg[0] == arg[ft_strlen(arg) - 1])
		{
			new = ft_substr(arg, 1, ft_strlen(arg) - 2);
			free(*ptr);
			*ptr = new;
		}
	}
}

static int	invalid_token(char *arg, int i)
{
	if (arg && (arg[0] == '\'' || arg[0] == '\"'))
	{
		if (arg[0] != arg[ft_strlen(arg) - 1])
			return (i);
	}
	return (-1);
}

void	expand_dollar(char **ptr, t_shell *shell)
{
	int		i;
	int		f;
	char	*arg;
	char	*env;
	char	*tmp;

	i = 0;
	f = 0;
	arg = *ptr;
	while (arg && arg[i] && arg[i] != '\'')
	{
		if (arg[i++] == '$')
		{
			while (arg[i + f] && arg[i + f] != ' '
				&& arg[i + f] != '\"' && arg[i + f] != '$')
				f++;
			tmp = ft_substr(arg, i, f);
			env = env_get(tmp, shell->envp);
			free(tmp);
			tmp = free_join(ft_substr(arg, 0, i - 1), env, 1, 1);
			*ptr = free_join(tmp, ft_substr(arg, i + f, ft_strlen(arg)), 1, 1);
			expand_dollar(ptr, shell);
			return (free(arg));
		}
	}
}

void	combine_tokens(t_list **tokens, t_pipe **pipe, char *value, int *i)
{
	if ((*pipe)->argv[*i] == NULL)
	{
		if (!*tokens || (((t_token *)(*tokens)->content)
			&& ((t_token *)(*tokens)->content)->token == ' '))
		{
			*tokens = (*tokens)->next;
			return ;
		}
		(*pipe)->argv[*i] = ft_strdup(value);
	}
	else
		(*pipe)->argv[*i] = free_join((*pipe)->argv[*i], value, 1, 0);
	*tokens = (*tokens)->next;
	if (!*tokens || (((t_token *)(*tokens)->content)
		&& ((t_token *)(*tokens)->content)->token == ' '))
	{
		(*pipe)->argv = ft_realloc((*pipe)->argv, sizeof(char *) * (*i + 2));
		(*pipe)->argv[*i + 1] = NULL;
		(*i)++;
		if (*tokens)
			*tokens = (*tokens)->next;
	}
	(*pipe)->argc = *i;
}

void	expander(t_pipe *pipe, t_shell *shell)
{
	t_list	*tokens;
	char	*value;
	int		i;

	i = 0;
	pipe->envp = shell->envp;
	pipe->argc = 0;
	pipe->argv = mem_add(2, sizeof(char *));
	tokens = pipe->tokens;
	while (tokens)
	{
		value = ft_strdup(((t_token *)tokens->content)->value);
		pipe->invalid = invalid_token(value, i);
		expand_dollar(&value, shell);
		strip_quoted(&value);
		combine_tokens(&tokens, &pipe, value, &i);
		if (pipe->invalid != -1)
			break ;
		free(value);
	}
}
