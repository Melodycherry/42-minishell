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
}
