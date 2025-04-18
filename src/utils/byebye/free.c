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

// fonction qui va free toute la liste qui contient les tokens. 
// A modifier au besoin si on change de struct. 
void	free_token_list(t_shell *shell)
{
	t_token	*current;
	t_token	*next;

	if (!shell)
		return ;
	current = shell->tlist->head;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

// fonction pour free si un pb pendant la copie de tableau (genre envp)
void	free_mid_tab(char **tab, int i)
{
	while (i > 0)
	{
		i--;
		free (tab[i]);
	}
	free(tab);
	tab = NULL;
}

// la meme mais pour tout le tableau
void	free_tab(t_shell *shell, char **tab)
{
	int	i;

	i = 0;
	while (shell->cmd->envp_copy[i])
	{
		free (tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}
