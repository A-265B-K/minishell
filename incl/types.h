#ifndef TYPES_H
# define TYPES_H

# include "minishell.h"

typedef enum e_control_states
{
	EXIT,
	CONTINUE,
	EXTERNAL,
	BUILTIN
}	t_state;

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
	struct s_token			*next;
	struct s_token			*prev;
}	t_token;

typedef struct s_commands
{
	char	**str;
	char	*builtin;
	t_token	*tokenized;
	char	*redirection;
	int		id;
	struct	s_commands	*next;
	struct	s_commands	*prev;
}	t_commands;

typedef struct s_shell
{
	char			*prompt;
	char			*input;
	char			**envp;
	int				exitcode;
	bool			exit;
	t_token			*tokenized;
	t_token			*lexer_grouped;
	t_commands		*com_struct;
}	t_shell;



// typedef struct s_task
// {
// 	int				index;
// 	t_list			*tokens;
// 	t_list			*pipes;
// 	t_token_type	type;
// }	t_task;

// typedef struct s_pipe
// {
// 	int				index;
// 	int				invalid;
// 	pid_t			pid;
// 	t_list			*tokens;
// 	int				wstatus;
// 	char			**envp;
// 	char			**argv;
// 	int				argc;
// 	bool			is_exit;
// }	t_pipe;

// typedef struct s_env
// {
// 	char			*key;
// 	char			*value;
// }	t_env;

#endif