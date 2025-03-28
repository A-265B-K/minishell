/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 03:01:29 by marvin            #+#    #+#             */
/*   Updated: 2025/03/28 03:05:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "minishell.h"

typedef enum e_operators
{
	O_PIPE,
	O_AND,
	O_OR,
	O_LESS,
	O_DLESS,
	O_GREAT,
	O_DGREAT,
	O_WORD,
	O_SPACE,
	O_EMPTY,
	O_G_BUILTIN,
	O_G_REDIRECT,
	O_G_WORD,
}	t_operators;

typedef struct s_heredoc
{
	char				*delimiter;
	int					quoted;
	char				*tempfile;
	struct s_heredoc	*next;
}	t_heredoc;

typedef struct s_lexer_tools
{
	char	*buffer;
	int		id;
	int		mem_size;
	int		token_len;
	int		quote_flag;
	char	quote_type;
}	t_lexer_tools;

typedef struct s_token
{
	char			*str;
	char			c;
	int				id;
	t_operators		token;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_commands
{
	char				**str;
	char				*builtin;
	t_token				*tokenized;
	char				**redirection;
	int					red_count;
	char				*hd_name;
	int					id;
	struct s_commands	*next;
	struct s_commands	*prev;
}	t_commands;

typedef struct s_q
{
	int	in_s;
	int	in_d;
	int	i;
	int	j;
}	t_q;

typedef struct s_shell
{
	char			*prompt;
	char			*input;
	char			**envp;
	int				exitcode;
	char			*cur_pwd;
	char			*old_pwd;
	int				heredoc_id;
	int				quoted;
	t_token			*tokenized;
	t_token			*lex;
	t_commands		*com_struct;
}	t_shell;

#endif