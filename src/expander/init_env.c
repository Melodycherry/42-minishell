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

// fonction qui gere les copies de tableau
void	cpy_envp(t_shell *shell, char **envp)
{
	if (!envp || !envp[0])
		shell->cmd.envp_copy = malloc(sizeof(char *) * (ft_tablen(envp)) + 1);
	else
	{
		shell->cmd.envp_copy = cpy_tab(envp);
		shell->cmd.envp_exp = cpy_tab(envp);
		bubble_tab(shell->cmd.envp_exp);
	}
}


