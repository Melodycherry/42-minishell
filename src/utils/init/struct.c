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
	init_list(shell);
	shell->cmd->line = 0;
	shell->cmd->envp_copy = 0;
	shell->cmd->path = 0;
	shell->cmd->prompt = 0;
}
