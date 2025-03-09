/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: alkuijte <alkuijte@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/09 12:58:04 by alkuijte      #+#    #+#                 */
/*   Updated: 2025/03/09 12:58:04 by alkuijte      ########   odam.nl         */
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
# include <unistd.h>

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "types.h"
# include "errors.h"
# include "colors.h"

int					main(int argc, char **argv, char **envp);
int					ft_strcmp2(const char *s1, const char *s2);
int					execute_cmd(t_shell *shell, t_commands *cmd, int pipe_fd);
char				*ft_strlcpy2(char *str, int c);
int					execute_builtin(t_shell *shell, t_commands *cmd);
int					redirection_permission(t_commands *cmd);
void				close_shell(t_shell *shell);
int					error(char *str);
void				*mem_add(size_t count, size_t size);
char				*free_join(char *s1, char *s2, bool free_s1, bool free_s2);
char				**alloc_double(char **envp);
int					ft_strarrlen(char **arr);
void				free_double(char **str);
void				execute_pipe(t_shell *shell, t_commands *cmd);
void				handle_redirects(t_commands *cmd);
int					redirect_and_execute(t_shell *shell, t_commands *cmd, \
										int pipe_fd);
char				*ft_getenv(const char *name);
int					ft_unsetenv(char **params);
int					ft_pwd(void);
int					ft_echo(char **params);
int					ft_env(void);
int					ft_export(char **params);
int					ft_cd(char **params);
void				ft_exit(char **params, int exitcode);
int					ft_isstrnum(char *str);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_setenv(const char *name, const char *value);
char				**ft_split(const char *str, char delimiter);
void				ft_bzero(void *s, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
int					ft_isdigit(int c);
int					ft_atoi(const char *str);
int					ft_setenv(const char *name, const char *value);
char				*env_get(char *str, char *envp[]);
const char *const	*borrow_env(void);
int					lexer(t_shell *shell);
t_token				*tokenize_input(const char *input);
int					handle_operator(const char *input, int i, \
									t_token **head, int *id);
int					handle_quotes(const char *input, int start, \
									t_token **head, int *id);
int					handle_word(const char *input, int i, \
									t_token **head, int *id);
int					is_operator(char c);
t_operators			identify_operator(char c, char c_plus);
int					ft_strcmp2(const char *s1, const char *s2);
void				free_tokens(t_token *head);
void				token_add_back(t_token **head, t_token *new_token);
t_token				*create_token(char *str, char c, int id, t_operators token);
void				print_tokens(t_token *head);
t_token				*group_tokens(t_token *lexer_input);
void				print_grouped(t_token *head);
void				append_to_buffer(t_lexer_tools *tools, char c);
void				handle_operator_token(t_token **lexer_grouped, \
									t_token **current, t_lexer_tools *tools);
void				finalize_token(t_token **lexer_grouped, \
									t_lexer_tools *tools, t_operators type);
void				init_lexer_tools(t_lexer_tools *tools);
int					group_quotes(t_token **current, char c);
int					is_f_operator(char c);
char				*search_env(char **env, char *target);
void				parser(t_shell *shell);
void				handle_redirection(t_commands *command, t_token *current);
int					identify_builtin(t_commands *command, t_token *current);
t_commands			*parse_tokens(t_token *lexer_grouped);
int					operator_placement(t_shell *shell);
int					syntax_check(t_shell *shell);
int					operator_check(char *str);
int					unclosed_quotes(const char *input);
void				add_command_to_list(t_commands **commands, \
					t_commands *new_command);
t_commands			*create_command_node(int count);
void				free_command_node(t_commands *command);
int					execute(t_shell *shell);
int					error_handler(char *str, int exitcode);

#endif