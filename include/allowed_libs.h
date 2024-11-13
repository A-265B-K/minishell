
#ifndef ALLOWED_LIBS_H
# define ALLOWED_LIBS_H

// LibFT
# include "../lib/libft/include/libft.h"

// Printf, perror, strerror
# include <stdio.h>

// Malloc, free, exit, getenv
# include <stdlib.h>

// Write, Access, Close, Fork, Execve, getcwd, chdir,
// unlink, dup, dup2, pipe, isatty, ttyname, ttyslot
# include <unistd.h>

// Open
# include <fcntl.h>

// Read
# include <sys/types.h>
# include <sys/uio.h>

// Wait, Wait3, Wait4
# include <sys/wait.h>

// Waitpid
# include <sys/wait.h>
# include <sys/types.h>

// Signal, Sigaction, Sigemptyset, Sigaddset, Kill
# include <signal.h>

// stat, lstat, fstat
# include <sys/stat.h>

// opendir, readdir, closedir
# include <dirent.h>

// strerror
# include <string.h>
# include <errno.h>

// ioctl
# include <sys/ioctl.h>

// tcsetattr
# include <termios.h>

# include <stdbool.h>

// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <curses.h>
# include <term.h>

// readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history
# include <readline/readline.h>
# include <readline/history.h>

#endif