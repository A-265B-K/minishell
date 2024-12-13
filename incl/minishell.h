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

# include "../libft/incl/libft.h"

# include <readline/readline.h>
# include <readline/history.h>

# include "types.h"
# include "errors.h"
# include "colors.h"
# include "functions.h"
# include "declarations.h"

// MINISHELL
// minishell.c
// void	ft_list_semi_clear(t_list **lst);
// void	free_t_pipe(void *ptr);
// int		clean_exit(t_shell *shell);
int		main(int argc, char **argv, char **envp);

// // TOOLS
// // tools/array.c
// int		ft_strarrlen(char **arr);
// // tools/debug.c
// int		b_debug(int argc, char **argv, char **envp, t_shell *shell);
// void	debug(char *str);
// void	print_shell(t_shell *s);
// // tools/errors.c
int		error(char *str);
// // tools/mem.c
void	*mem_add(size_t count, size_t size);
// void	*ft_realloc(void *ptr, size_t size);
// char	*free_join(char *s1, char *s2, bool free_s1, bool free_s2);

// // TOKENIZER
// // tokenizer/operators.c
// int		is_operator(char c);
// int		get_double_operator(const char *str, t_list **list);
// int		get_single_operator(const char *str, t_list **list);
// // tokenizer/parameters.c
// int		get_param(const char *str, t_list **list);
// // tokenizer/quotes.c
// int		is_quote(const char *str);
// int		get_quote(const char *str, t_list **list);
// // tokenizer/words.c
// int		get_word(const char *str, t_list **list);
// // tokenizer/tokenizer.c
// void	free_t_token(void *token);
// void	tokenizer(t_shell *shell);

// // SIGNALS
// // signals/signals.c
// void	signal_init(void);
// void	signal_handler(int signum);
// void	signal_handler_forked(int signum);

// // READLINE
// // readline/readline.c
// void	set_prompt(char *envp[], t_shell *shell);
// void	readline_init(t_shell *shell);

// // PARSER
// // parser/parser.c
// void	parser(t_shell *shell);
// // parser/tasks.c
// void	free_t_tasks(void *ptr);
// void	break_tasks(t_shell *shell);
// // parser/pipes.c
// void	free_t_pipe(void *ptr);
// void	break_pipes(t_task *task);

// // HISTORY
// // history/history.c
// void	history_init(t_shell *shell);
// void	history_add(char *line, t_shell *shell);

// // FILES
// // file/file.c
// char	*file_searchpath(char *filename, char *envp[]);

// // EXECUTE
// // execute/execute.c
// char	*where(char *arg, t_shell *shell);
// t_state	execute(t_shell *shell);
// void	print_pipe(t_pipe *pipes); //temp

// // EXPANDER
// // expander/expander.c
// void	expander(t_pipe *pipe, t_shell *shell);

// // ENVIRONMENT
// // env/env.c
// char	**env_get_searchpaths(char *envp[]);
// char	*env_get(char *str, char *envp[]);
// bool	env_set(char *str, char *envp[]);
// bool	env_add(char *str, char ***envp);

// // BUILTINS
// typedef int	(*t_function)(int argc, char **argv, char **envp, t_shell *shell);

// int		builtins(int argc, char **argv, char **envp, t_shell *shell);
// int		pwd(int argc, char **argv, char **envp, t_shell *shell);
// void	export_add(char **argv, t_shell *shell);
// // builtins/echo.c
// int		b_echo(int argc, char **argv, char **envp, t_shell *shell);
// // builtins/cd.c
// int		cd(int argc, char **argv, char **envp, t_shell *shell);
// // builtins/env.c
// int		env(int argc, char **argv, char **envp, t_shell *shell);
// // builtins/exit.c
// int		b_exit(int argc, char **argv, char **envp, t_shell *shell);

// void	export_copy(char **env_temp, t_shell *shell, int i);
// void	export_switch(char **env_temp, t_shell *shell, int j);
// int		b_export(int argc, char **argv, char **envp, t_shell *shell);
// // void	print_export(char **env_temp);
// void	export_add(char **argv, t_shell *shell);
// bool	export_check(char **argv);
// int		dupe_check(char *argv, char **envp);
// // void	*ft_memdelete(void *pointer);
// char	**array_add_back(char **strs, const char *str);
// void	env_replace(char **old_envp, const char *replace);
// char	*variable_find(char *argv);
// // builtin/unset
// int		unset_find_line(char *argv, char **s_envp);
// int		unset(int argc, char **argv, char **envp, t_shell *shell);
// char	**array_remove_line(char **strs, int line);
// void	unset_line(char ***envp, int line);

// // tools/array.c
// int		ft_strarrlen(char **arr);
// void	free_double(char **str);
// void	print_double(char **str);

#endif
