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

static void	init_list(t_shell *shell);
static void	init_executor(t_shell *shell);

void	init_all(t_shell *shell)
{
	init_list(shell);
	init_executor(shell);
	shell->executor.is_forked = FALSE;
	shell->lexer.space = 0;
	shell->lexer.double_quote = 0;
	shell->lexer.single_quote = 0;
}

// initiation de listes
// testée a l air ok
static void	init_list(t_shell *shell)
{
	shell->tlist.head = NULL;
	shell->tlist.token_cnt = 0;
}

static void	init_executor(t_shell *shell)
{
	shell->executor.end = 0;
	shell->executor.start = 0;
	shell->executor.nb_pipe = 0;
	shell->executor.nb_redir = 0;
	shell->executor.redir_type = 0;
	shell->executor.nb_heredoc = 0;
	shell->executor.nb_redir_wip = 0;
	shell->executor.index_file_heredoc = 0;
	shell->executor.av = NULL;
	shell->executor.paths = NULL;
	shell->executor.pipe_av = NULL;
	shell->executor.redir_av = NULL;
	shell->executor.redir_file = NULL;
}
