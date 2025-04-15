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

// fonction qui va free toute la liste qui contient les tokens. A modifier au besoin si on change de struct. 
void    free_token_list(t_shell *shell)
{
	t_token  *current;
	t_token  *next;

	if (!shell)
		return ;
	
	current = shell->list->head;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

// fonction pour free si un pb pendant la creation de la copie de l'envp ou autre tableau qu on voudrait copier ?
char	**free_mid_tab(char **strs, int i)
{
	while (i > 0)
	{
		i--;
		free (strs[i]);
	}
	free(strs);
	return (NULL);
}

// la meme mais pour tout le tableau
char	**free_tab(t_shell *shell, char **tab)
{
	int	i;

	i = 0;
	while (i < shell->cmd->envp_copy)
	{
		free (tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

// je me pose la question de la necessité du char ** sur les free tab et freemidtab 