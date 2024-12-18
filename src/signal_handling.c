# include <minishell.h>

void	handler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGINT)
		ft_printf_fd(1, "\n"); // Replace with proper printf
	if (sig == SIGHUP)
		ft_exit(NULL);
}

void	signal_handling(int fd)
{
	struct	sigaction	s_sigaction;

	(void)fd;

	s_sigaction.sa_sigaction = handler;
	s_sigaction.sa_flags = SA_SIGINFO;
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &s_sigaction, NULL);
	sigaction(SIGHUP, &s_sigaction, NULL);
}
