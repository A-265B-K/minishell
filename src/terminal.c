# include <minishell.h>

void	disable_std_behaviour(void)
{
	struct termios oldt;
	struct termios newt; //check if functions here need protection

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &newt);
}

void	enable_std_behaviour(void)
{
	struct termios oldt;

	tcgetattr(STDIN_FILENO, &oldt);
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}
