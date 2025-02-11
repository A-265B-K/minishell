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

char	*env_get(char *str, char *envp[]);

int	lexer(t_shell *shell);
t_token *tokenize_input(const char *input);
int	handle_operator(const char *input, int i, t_token **head, int *id);
int	handle_quotes(const char *input, int start, t_token **head, int *id);
int handle_word(const char *input, int i, t_token **head, int *id);
int	is_operator(char c);
t_operators	identify_operator(char c, char c_plus);

void	free_tokens(t_token *head);
void token_add_back(t_token **head, t_token *new_token);
t_token *create_token(char *str, char c, int id, t_operators token);
void print_tokens(t_token *head);
t_token *group_tokens(t_token *lexer_input);
void print_grouped(t_token *head);
void append_to_buffer(t_lexer_tools *tools, char c);
void handle_operator_token(t_token **lexer_grouped, t_token **current, t_lexer_tools *tools);
void finalize_token(t_token **lexer_grouped, t_lexer_tools *tools, t_operators type);
void init_lexer_tools(t_lexer_tools *tools);
int group_quotes(t_token **current, char c);
int is_f_operator(char c);
char	*search_env(char **env, char *target);

void	parser(t_shell *shell);
void handle_redirection(t_commands *command, t_token *current);
int identify_builtin(t_commands *command, t_token *current);
t_commands *parse_tokens(t_token *lexer_grouped);

int	operator_placement(t_shell *shell);
int	syntax_check(t_shell *shell);
int	operator_check(char *str);
int unclosed_quotes(const char *input);

void add_command_to_list(t_commands **commands, t_commands *new_command);
t_commands *create_command_node(int count);
void free_command_node(t_commands *command);
int execute(t_shell *shell);

#endif