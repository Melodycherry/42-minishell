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

void	free_mid_tab(char ***tab, int i)
{
	if (!tab && !*tab)
		return ;
	while (i > 0)
	{
		i--;
		free_ptr((void **)&((*tab)[i]));
	}
	free(*tab);
	*tab = NULL;
}

void	free_tab(char ***tab)
{
	int	i;

	i = 0;
	if (!tab || !*tab)
		return ;
	while ((*tab)[i])
	{
		free_ptr((void **)&((*tab)[i]));
		i++;
	}
	free(*tab);
	*tab = NULL;
}
