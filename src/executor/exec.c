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

void	execution(t_shell *shell)
{
	t_token *current;
	current = shell->tlist.head;
	
	
	while (current)
	{

	}
}

int create_av(t_shell *shell)
{
	int 	i;
	int		len;
	char	 **tab;
	t_token	*current;

	i = 0;
	current = shell->tlist.head;
	tab = malloc(sizeof(tab) * (shell->tlist.token_cnt + 1));
	while (i < shell->tlist.token_cnt)
	{
		len = ft_strlen(current->value);
		current = current->next;
		i++;
	}
}

//execve : prend : pathname, **av, **envp

