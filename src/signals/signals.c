/*****************************************************************************/
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*      LES CODEUSES DU DIMANCHE                                             */
/*      FONT UN MINISHELL                                                    */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "minishell.h"

static void	sigint_handler(int sig);

int		g_exit_status = 0;

void	parent_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
static void	sigint_handler(int sig)
{
	write (1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_status = sig;
}
void	handle_signal(t_shell *shell)
{
	if (g_exit_status == SIGINT)
		set_exit_status_env(shell, 130);
	g_exit_status = 0;
}

void	signal_heredoc(int sig) // special pour heredoc ? 
{
	(void)sig;
	write(1, "\n", 1);
	exit(130);
}
// faire laaaa gestioonnnnnn des signauuuuux