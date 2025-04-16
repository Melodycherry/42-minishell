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

// fonction pour connaitre le nb de row d un tableau
int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

// fonction pour copier le tableau des env recu dans cmd
char	**cpy_tab(t_shell *shell)
{
	int 	i;
	char	**cpy_tab;

	i = 0;
	cpy_tab = malloc(sizeof(char *) * (ft_tablen(shell->cmd->envp) + 1));
	if (!cpy_tab)
		return (NULL);
	while (i < ft_tablen(shell->cmd->envp))
	{
		cpy_tab[i] = ft_strdup(shell->cmd->envp[i]);
		if (cpy_tab[i] == NULL)
 			free_mid_tab(cpy_tab, i);
 		i++;
	}
	cpy_tab[i] = 0;
	return (cpy_tab);
}
