/*******************************************************************************/
/*                                                                             */
/*                                                                             */
/*                                                                             */
/*                                                                             */
/*      LES CODEUSES DU DIMANCHE                                               */
/*      FONT UN MINISHELL                                                      */
/*                                                                             */
/*                                                                             */
/*                                                                             */
/*******************************************************************************/

#include "minishell.h"


/** 
 * Executes the builtin env command: Prints the environment variables.
 */
void	builtin_env(t_shell *shell)
{
	char	**envp;

	envp = shell->cmd.envp_copy;
	if (!envp)
		return;
	print_tab(envp);
}

// juste printer le tableau de env. 
// that-s it ?