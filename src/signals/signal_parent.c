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
static void	sigquit_handler(int sig);

void	parent_signal(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	heredoc_parent_signal(void)
{
	signal(SIGINT, sigint_handler_child);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_core_dump_parent_signal(void)
{
	signal(SIGINT, sigint_handler_child);
	signal(SIGQUIT, sigquit_handler);
}

static void	sigint_handler(int sig)
{
	write (1, "\n", STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_status = sig;
}

static void	sigquit_handler(int sig)
{
	(void)sig;
	write (1, "\n", 1);
}
