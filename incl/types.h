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

// typedef enum e_operators
// {
	
// }	t_operators;

// typedef struct s_token
// {
// 	char			*raw;
// 	char			*value;
// 	t_token_type	token;
// }	t_token;

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

typedef struct s_shell
{
	char			*prompt;
	// bool			debug;
	char			*input;
	char			**envp;
	int				exitcode;
	bool			exit;
	// t_list			*env;
	// t_list			*tokens;
	// t_list			*tasks;
	// int				pipe_fd[2];
	// int				std_fd[2];
	// HIST_ENTRY		**history_entry;
	// HISTORY_STATE	*history_state;
}	t_shell;

#endif