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

// initialisation des structures, a mettre en premier dans le main :), 
// a decouper en plusieurs si trop long && mettre a jour
void	init_all(t_shell *shell)
{
	init_list(shell); // le probleme etait la, c'etait pas decommente
	//shell->cmd->path = 0;
	shell->lexer.double_quote = 0;
	shell->lexer.single_quote = 0;
	shell->lexer.space = 0;
	shell->executor.av = NULL;
	shell->executor.end = 0;
	shell->executor.is_forked = FALSE;
	shell->executor.nb_pipe = 0;
	shell->executor.nb_redir = 0;
	shell->executor.paths = NULL;
	shell->executor.pipe_av = NULL;
	shell->executor.redir_file = NULL;
	shell->executor.redir_type = 0;
	shell->executor.start = 0;
}
