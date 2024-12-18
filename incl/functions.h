
// Miscelanous
int		error_handling(char *error_message);
char	*recursive_strcat(char **strs);
char	**get_function_name(const char *str);
void	signal_handling(int	fd);

// Builtins
int	function_call(int fd, char *parameters, t_shell *tstruct);
int	ft_cd(int fd, char **params);
void	ft_exit(char **params);

// Environ
const char *const *borrow_env(void);
char *ft_getenv(const char *name);

// Terminal
void	enable_std_behaviour(void);
void	disable_std_behaviour(void);
