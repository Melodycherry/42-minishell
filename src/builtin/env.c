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
