/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: marvin <marvin@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/28 02:38:40 by marvin        #+#    #+#                 */
/*   Updated: 2025/03/28 13:34:30 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# ifdef __linux__
#  include <linux/limits.h>
# else
#  include <limits.h>
# endif
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h> 
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "types.h"

// clean_shell.c
void		reset_shell(t_shell *shell);
void		close_shell(t_shell *shell);

// env_tools.c
char		*ft_env_get(char *str, char **envp);

// error.c
void		print_command_error(char *cmd);
void		path_error(t_commands *cmd);
int			error_handler(char *str, int exitcode);

// exe_builtins.c
int			ft_pwd(t_shell *shell);
int			is_flag(char *str);
int			ft_echo(char **params);
int			ft_env(t_shell *shell);
int			execute_builtin(t_shell *shell, t_commands *cmd);

// exe_cd.c
int			ft_cd(char **str, char ***envp, t_shell *shell);
int			check_chdir(char **str, t_shell *shell);
int			update_env_var(char ***envp, char *var_name, char *value);
int			find_var(char ***envp, char *var, size_t name_len, char *new);

// exe_exit.c
int			ft_isstrnum(char *str);
void		ft_exit(char **params, int exitcode);

// exe_export.c
char		**add_new_var(char **envp, char *new_var, int count);
int			count_env_vars(char **envp);
int			valid_id_check(const char *name);
int			set_env_var(char ***envp, char *new_var);
int			ft_export(char **cmd, char ***envp);

// exe_main.c
char		*check_absolute_path(char *cmd);
char		*get_command_path(char *cmd, t_shell *shell);
int			is_single_builtin(t_shell *shell);
void		execute_external(t_commands *cmd, t_shell *shell);
int			execute(t_shell *shell);

// exe_pipes.c
int			exe_pipe(t_shell *shell, t_commands *cmd, int *prev_p, int *cur_p);
void		close_pipe_ends(int prev_p, int *cur_p, t_commands *cmd);
int			wait_for_children(void);
int			execute_pipes(t_shell *shell);

// exe_redirects.c
void		set_pipe_redir(int prev_in, int *curr_pipe, t_commands *cmd);
void		redirect(char *redir, int is_last_command);
void		set_child_redir(int prev_in, int *curr_pipe, t_commands *cmd);

// exe_tools.c
char		*ft_strtok(char *str, const char *delim);
void		rm_empty_str(t_commands *cmd);
void		ft_non_binary(char *full_path, char **envp);

// exe_unset.c
char		*ft_getenv(const char *name, t_shell *shell);
int			ft_unsetenv(char **params, t_shell *shell);
int			valid_identifier_check(const char *name);

// export_tools.c
char		**duplicate_envp(char **envp, int count);
void		sort_envp(char **sorted_envp, int count);
void		print_env_sorted(char **envp);
int			get_var_name_len(char *new_var);
int			find_var_index(char **envp, char *new_var, int len);

// heredoc_tools.c
int			write_to_tempfile(const char *filename, const char *content);
char		*create_tempfile(t_shell *shell);

// heredoc.c
int			handle_heredoc(t_commands *cmd, t_token *token, t_shell *shell);
char		*check_hd_quote(char *lim, t_shell *shell);
int			hd_to_cmd(t_commands *cmd, char *file_name);
char		*expand_hd(char *line, t_shell *shell, int quoted, char *content);

// lexer_group.c
t_token		*group_tokens(t_token *lexer_input, t_lexer_tools tools, int err);
int			quote_group(t_token **current, t_lexer_tools *tools);
int			group_quotes(t_token **current, char c);
int			build_group(t_token *current, t_token **lex, t_lexer_tools *tools);

// lexer_tokens.c
t_token		*tokenize_input(char *input, int id, int i);
int			handle_operator(char *input, int i, t_token **head, int *id);
int			handle_quotes(char *input, int start, t_token **head, int *id);
int			handle_word(char *input, int i, t_token **head, int *id);
t_operators	id_op(char c, char c_plus);

// lexer_tools.c
int			is_f_operator(char c);
void		free_tokens(t_token **head);
int			token_back(t_token **head, t_token *new_token);
t_token		*c_token(char *str, char c, int id, t_operators token);

// lexer.c
int			lexer(t_shell *shell);
int			append_to_buffer(t_lexer_tools *tools, char c);
int			op_token(t_token **lex, t_token **current, t_lexer_tools *tools);
int			fin_tok(t_token **lex, t_lexer_tools *tools, t_operators type);
int			init_lexer_tools(t_lexer_tools *tools);

// minishell.c
int			main(int argc, char **argv, char **envp);
int			run_shell(t_shell *shell);
t_shell		*shell_init(char **envp);
void		set_prompt(t_shell *shell);

// parse_actions.c
int			parse_redir(t_commands *command, t_token *current, t_shell *shell);
int			identify_builtin(t_commands *command, t_token *current);
int			parse_pipe(t_commands **com, t_commands **c_com, int node_count);
int			parse_builtin(t_token *c_tok, t_commands *c_com, int arg_count);
int			p_redir(t_commands *c_com, t_token **c_tok, int c, t_shell *shell);

// parse_quotes.c
int			handle_exitcode(char **result, t_q *q, t_shell *shell, char *s);
void		toggle_quotes(char c, t_q *q);
void		init_q(t_q *q);
int			handle_exp(char *input, char **result, t_shell *shell, t_q *q);
void		handle_regular_char(const char *input, char **result, t_q *q);

// parser_expand.c
int			variable_expansion(char *ip, char **result, t_q *q, t_shell *shell);
char		*expand_env_var(char *var, t_shell *shell);
int			var_len(const char *input, int *i);

// parser_tools.c
int			ft_isvalid(int c);
char		*rm_quotes(char *str);
void		free_command_list(t_commands *commands);
void		add_command_to_list(t_commands **commands, t_commands *new_command);
t_commands	*create_command_node(int count);

// parser.c
int			parser(t_shell	*shell);
int			quotes_in_redirects(t_commands *cmd);
char		*expand_quotes(char *s, t_shell *shell);
int			quotes_in_commands(t_commands *cmd, t_shell *shell, char *temp);
t_commands	*parse_tokens(t_token *lex, int ac, int nc, t_shell *shell);

// signals.c
void		setup_signals(void);
void		handle_sigquit(int sig);
void		handle_sigint(int sig);

// syntax_tools.c
int			ft_isspace(char c);
int			ft_isquote(char c);
int			unclosed_quotes(const char *input);
int			check_hd(char *str);
int			valid_combo(char *str, int i);

// syntax.c
int			syntax_check(t_shell *shell);
int			increment_quote(char *str, int i);
int			combo_check(char *str);
int			operator_check(char *str);
int			operator_placement(t_shell *shell);

// tools_two.c
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strjoin3(const char *s1, const char *s2, const char *s3);
char		*ft_strlcpy2(char *str, int c);
int			ft_strcmp2(const char *s1, const char *s2);
char		**env_to_array(t_shell *shell);

// tools.c
void		*mem_add(size_t count, size_t size);
char		**alloc_double(char **envp);
int			ft_strarrlen(char **arr);
void		free_double(char **str);
char		*free_join(char *s1, char *s2, bool free_s1, bool free_s2);

#endif