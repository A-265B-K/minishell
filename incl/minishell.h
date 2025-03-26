#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef DEBUG
#  define DEBUG 1
# endif

# ifndef EXTRA
#  define EXTRA 1
# endif

# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <ctype.h>
# include <errno.h>
# include <curses.h>
# include <term.h>
# include <dirent.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# ifdef __linux__
#  include <linux/limits.h>
# else
#  include <limits.h>
#endif
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <unistd.h>

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "types.h"
# include "errors.h"
# include "colors.h"

int		main(int argc, char **argv, char **envp);
void	close_shell(t_shell *shell);
int		error(char *str);
void	*mem_add(size_t count, size_t size);
char	*free_join(char *s1, char *s2, bool free_s1, bool free_s2);
char	**alloc_double(char **envp);
int		ft_strarrlen(char **arr);
void	free_double(char **str);

char	*ft_getenv(const char *name, t_shell *shell);
// int ft_pwd(void);
// int ft_echo(char **params);
// int ft_env(void);
// int ft_export(char **params);
// int ft_cd(char **params);
void ft_exit(char **params, int exitcode);
int ft_isstrnum(char *str);
int ft_strcmp(const char *s1, const char *s2);
int ft_setenv(const char *name, const char *value);
char **ft_split(const char *str, char delimiter);
void ft_bzero(void *s, size_t n);
size_t ft_strlcpy(char *dst, const char *src, size_t dstsize);
int ft_isdigit(int c);
int ft_atoi(const char *str);
int ft_setenv(const char *name, const char *value);
char	*env_get(char *str, char *envp[]);
const char *const *borrow_env(void);
int	ft_strcmp2(const char *s1, const char *s2);

int	operator_placement(t_shell *shell);
int	syntax_check(t_shell *shell);
int	operator_check(char *str);
int unclosed_quotes(const char *input);

int execute(t_shell *shell);


// lexer.c
int		lexer(t_shell *shell);
void	append_to_buffer(t_lexer_tools *tools, char c);
void	op_token(t_token **lex, t_token **current, t_lexer_tools *tools);
void	finalize_token(t_token **lex, t_lexer_tools *tools, t_operators type);
void	init_lexer_tools(t_lexer_tools *tools);

// lexer_tokens.c
t_token		*tokenize_input(const char *input);
int			handle_operator(const char *input, int i, t_token **head, int *id);
int			handle_quotes(const char *input, int start, t_token **head, int *id);
int			handle_word(const char *input, int i, t_token **head, int *id);
t_operators	id_op(char c, char c_plus);

// lexer_group.c
t_token	*group_tokens(t_token *lexer_input);
int		quote_group(t_token **current, t_lexer_tools *tools, t_token **lex);
int		group_quotes(t_token **current, char c);

// lexer_tools.c
int		is_f_operator(char c);
int		is_operator(char c);
void	free_tokens(t_token **head);
void	token_back(t_token **head, t_token *new_token);
t_token	*c_token(char *str, char c, int id, t_operators token);

// parser.c
t_commands  *parse_tokens(t_token *lex, int arg_count, int node_count, t_shell *shell);
int			variable_expansion(const char *input, char **result, t_q *q, t_shell *shell);
char        *remove_quotes(const char *input, t_shell *shell);
void        quotes_in_commands(t_commands *cmd, t_shell *shell);
int			parser(t_shell	*shell);

// parse_actions.c
int		handle_redirection(t_commands *command, t_token *current, t_shell *shell);
int	    identify_builtin(t_commands *command, t_token *current);
int	    parse_pipe(t_commands **com, t_commands **c_com, int node_count);
int	    parse_builtin(t_token *c_tok, t_commands *c_com, int arg_count);
int	    parse_help(t_commands *c_com, t_token **c_tok, int arg_count, t_shell *shell);

// parse_env.c
char        *expand_env_var(const char *var, t_shell *shell);
void		toggle_quotes(char c, t_q *q);
int	        handle_exitcode(char **result, t_q *q, t_shell *shell);
int			ft_isvalid(int c);

// parser_tools.c
t_commands	*create_command_node(int count);
void        add_command_to_list(t_commands **commands, t_commands *new_command);
void        free_command_list(t_commands *commands);
void	    free_command_node(t_commands *command);
int         var_len(const char *input, int *i);

// testing.c
void	print_tokens(t_token *head);
void	print_grouped(t_token *head);
void	print_parser(t_commands *commands);
void    print_array(char **str);

// exe_main.c
int	execute_string(t_shell *shell, t_commands *cmd, char *str, int pipe_fd);
int	check_perms(t_shell *shell, t_commands *cmd, char *bin, struct stat statbuf, int pipe_fd);
int	execute_binaries(t_shell *shell, t_commands *cmd, int pipe_fd);
// static int	execute_files(t_shell *shell, t_commands *cmd, int pipe_fd);
int	execute_cmd(t_shell *shell, t_commands *cmd, int pipe_fd);
int	execute(t_shell *shell);
char *ft_strjoin3(const char *s1, const char *s2, const char *s3);
char	*ft_strlcpy2(char *str, int	c);
int	ft_strcmp2(const char *s1, const char *s2);

// exe_redirections
// static void	clean_redir(t_commands *cmd, int sin, int sout, int serr);
int	redirection_permission(t_commands *cmd);
// static int	redirection_dup(t_shell *shell, t_commands *cmd);
int	redirect_and_execute(t_shell *shell, t_commands *cmd, int pipe_fd);
void	handle_redirects(t_commands *cmd);

// exe_pipes.c
// static void	execute_child(t_shell *shell, t_commands *cmd, int fd[2], int *pipe_fd);
int	run_pipe(t_shell *shell, t_commands *cmd, int pipe_fd, int *child_exitcode);
void	execute_pipe(t_shell *shell, t_commands *cmd);

// exe_builtins.c
int	ft_pwd(void);

int ft_echo(char **params);
int	is_flag(char *str);

int	ft_env(t_shell *shell);

// int	ft_export(char **params);
int ft_export(char **cmd, char ***envp);

int	ft_unsetenv(char **params, t_shell *shell);
int	set_env_var(char ***envp, char *new_var);
int	ft_isstrnum(char *str);
// int	ft_cd(char	**params);
int	ft_strcmp(const char *s1, const char *s2);
void	ft_exit(char **params, int exitcode);
int	execute_builtin(t_shell *shell, t_commands *cmd);
int	valid_id_check(const char *name);

// exe_tools.c
int	is_dir(const char *file_path);
int	error_handler(char *str, int exitcode);

int handle_heredoc(t_commands *cmd, t_token *token, t_shell *shell);
int update_env_var(char ***envp, char *var_name, char *value);
int ft_cd(char **argv, char ***envp);
#endif