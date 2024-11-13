
#include "../../include/minishell.h"

void	signal_init(void)
{
	signal(SIGHUP, SIG_IGN);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	if (signum == SIGQUIT)
		exit(131);
}

void	signal_handler_forked(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
	}
	if (signum == SIGQUIT)
		exit(131);
}
