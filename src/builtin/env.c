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
	if (!shell->cmd.envp_copy)
	{
		printf("no env bitch\n");
		return;
	}
	print_tab(shell->cmd.envp_copy);
}
//fonction de test pour voir si la copie du tableau s est bien faite.
void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}