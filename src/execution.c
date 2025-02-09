# include <minishell.h>
#include <errno.h>
// make it so the last command is executed in the parent


int	ft_strcmp2(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (unsigned char)(*s1) - (unsigned char)(*s2);
}

void	execute_builtin(t_shell *shell, t_commands *cmd)
{
	if(!ft_strcmp2(cmd->builtin, "pwd"))
			shell->exitcode = ft_pwd();
	else if(!ft_strcmp2(cmd->builtin, "echo"))
			shell->exitcode =ft_echo(cmd->str, shell);
	else if(!ft_strcmp2(cmd->builtin, "cd"))
			shell->exitcode = ft_cd(cmd->str);
	else if(!ft_strcmp2(cmd->builtin, "export"))
			shell->exitcode = ft_export(cmd->str);
	else if(!ft_strcmp2(cmd->builtin, "unset"))
			shell->exitcode = ft_unsetenv(cmd->str);
	else if(!ft_strcmp2(cmd->builtin, "env"))
			shell->exitcode = ft_env();
	else if(!ft_strcmp2(cmd->builtin, "exit"))
			ft_exit(cmd->str, shell->exitcode);
}

int	is_dir(const char *file_path)
{
	struct stat path_stat;
	if(!stat(file_path, &path_stat))
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}
int execute_cmd(t_shell *shell, t_commands *cmd) {
    if (cmd->builtin) {
        execute_builtin(shell, cmd);
        exit(0);
    }

    char *file_path;

    if (cmd->str[0][0] == '/' || cmd->str[0][0] == '.') {
        if (cmd->str[0][0] == '/') {
            file_path = ft_strjoin("/", cmd->str[0] + 1);
        } else if (cmd->str[0][0] == '.') {
            char buf[100];
            file_path = ft_strjoin(getcwd(buf, 100), cmd->str[0] + 1);
        }

        if (access(file_path, F_OK)) {
            dprintf(2, " No such file or directory\n");
            return 127;
        }
        if (access(file_path, R_OK) || access(file_path, W_OK) || access(file_path, X_OK)) {
            dprintf(2, " Permission denied\n");
            return 126;
        }
        if (!is_dir(file_path)) {
            dprintf(2, " Is a directory\n");
            return 126;
        }
    }

    pid_t pid = fork();
	int status;
    if (pid == 0) {
        char *function_name = ft_strjoin("/usr/bin/", cmd->str[0]);
        if (execve(function_name, cmd->str, (char *const *)borrow_env()) == -1) {
          //  function_name = ft_strjoin("./", cmd->str[0]);
            dprintf(2, " command not found\n");
            free(function_name);
            exit (127);
        }
    } else {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status); // Get child's exit code
        } else {
            return 1; // Some error occurred
        }
	}

    return 0;
}

int redirect_and_execute(t_shell *shell, t_commands *cmd) {
    int out_fd;
    pid_t pid;
    char *str = cmd->redirection;

    if (cmd->builtin && !cmd->next) {
        execute_builtin(shell, cmd);
        return 0;
    }

    if (!cmd->next) {
        shell->exitcode = execute_cmd(shell, cmd);
        return 0;
    }

    if (str) {
        if (str[1] == '>') {
            out_fd = open(str + 2, O_CREAT | O_WRONLY | O_APPEND, 0644);
        } else {
            out_fd = open(str + 1, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        }
        if (out_fd < 0) {
            perror("Open");
            return 1;
        }
    } else {
        out_fd = STDOUT_FILENO;
    }

    pid = fork();
    if (pid == 0) {
		if (out_fd >= 0 && out_fd != STDOUT_FILENO) {
	   	dup2(out_fd, STDOUT_FILENO);
	    close(out_fd);
	}
        exit (execute_cmd(shell, cmd));
    } else {
        waitpid(pid, NULL, 0);
        if (out_fd != STDOUT_FILENO) {
            close(out_fd);
        }
    }

    return 0;
}

void debug_fds(const char *msg) {
    printf("%s\n", msg);
    for (int fd = 0; fd < 10; fd++) {
        if (fcntl(fd, F_GETFD) != -1)
            dprintf(2, "FD %d is open\n", fd);
    }
}

int execute_pipes(t_commands *cmd, int input_fd, t_shell *shell) {
    int pipe_fd[2];
    pid_t pid;
    int out_fd = STDOUT_FILENO;
    char *str = cmd->redirection;

    if (cmd->next == NULL) {
        if (str) {
            if (str[1] == '>') {
                out_fd = open(str + 2, O_CREAT | O_WRONLY | O_APPEND, 0644);
            } else {
                out_fd = open(str + 1, O_CREAT | O_WRONLY | O_TRUNC, 0644);
            }
            if (out_fd < 0) {
                perror("Open");
                return -1;
            }
        }

        if (input_fd != STDIN_FILENO) {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }

        if (out_fd != STDOUT_FILENO) {
            dup2(out_fd, STDOUT_FILENO);
            close(out_fd);
        }

        return execute_cmd(shell, cmd);
    }

    if (pipe(pipe_fd) < 0) {
        perror("Pipe");
        return -1;
    }

    pid = fork();
    if (pid < 0) {
        perror("Fork");
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        return -1;
    }

    if (pid == 0) {
        close(pipe_fd[0]);
        dup2(input_fd, STDIN_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);

        if (str) {
            if (str[1] == '>') {
                out_fd = open(str + 2, O_CREAT | O_WRONLY | O_APPEND, 0644);
            } else {
                out_fd = open(str + 1, O_CREAT | O_WRONLY | O_TRUNC, 0644);
            }
            if (out_fd < 0) {
                perror("Open");
                exit(1);
            }
            dup2(out_fd, STDOUT_FILENO);
            close(out_fd);
        }

        if (execute_cmd(shell, cmd) == -1) {
            exit(1);
        }
        exit(0);
    }

    close(pipe_fd[1]);
    if (input_fd != STDIN_FILENO) {
        close(input_fd);
    }
    waitpid(pid, NULL, 0);

    return execute_pipes(cmd->next, pipe_fd[0], shell);
}

int handle_pipes(t_shell *shell, t_commands *cmd) {
    execute_pipes(cmd, STDIN_FILENO, shell);
    return 0;
}


int execute(t_shell *shell) {
    t_commands *cmd = shell->com_struct;

    if (cmd->next) {
        handle_pipes(shell, cmd);
    } else {
        redirect_and_execute(shell, cmd);
    }

    return 0;
}
