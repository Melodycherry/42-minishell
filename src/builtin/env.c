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
	int		i;
	char	**envp;

	i = 0;
	envp = shell->cmd.envp_copy;
	if (!envp)
		return;
	while (envp[i])
	{
		ft_printf("%s\n", envp[i]);
		i++;
	}
}

// juste printer le tableau de env. 
// that-s it ?