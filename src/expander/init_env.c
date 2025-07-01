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

void	cpy_envp(t_shell *shell, char **envp)
{
	shell->cmd.envp_copy = init_envp_copy(shell, envp);
	shell->cmd.envp_exp = cpy_tab(shell, envp);
	bubble_tab(shell->cmd.envp_exp);
}
