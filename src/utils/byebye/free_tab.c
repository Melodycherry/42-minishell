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

void	free_mid_tab(char **tab, int i)
{
	while (i > 0)
	{
		i--;
		free_ptr((void **)&tab[i]);
	}
	free(tab);
	tab = NULL;
}

void	free_tab(t_shell *shell, char ***tab)
{
	int	i;

	i = 0;
	(void)shell;
	if (*tab && tab)
	{
		while ((*tab)[i])
		{
			free_ptr((void **)&((*tab)[i]));
			i++;
		}
	}
	if (*tab)
	{
		free(*tab);
		*tab = NULL;
	}
}
