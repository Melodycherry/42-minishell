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
// A modifier au besoin si on change de struct. //free les strndup
void	free_token_list(t_shell *shell)
{
	t_token	*current;
	t_token	*next;

	if (!shell)
		return ;
	current = shell->tlist.head;
	while (current)
	{
		next = current->next;
		free_ptr((void **)&current->value);
		free_ptr((void **)&current->var_value);
		free(current);
		current = next;
	}
	shell->tlist.head = NULL;
}

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

void	free_tab(t_shell *shell, char **tab)
{
	int	i;

	i = 0;
	(void)shell;
	if (!tab)
		return ;
	while (tab[i])
	{
		free_ptr((void **)&tab[i]);
		i++;
	}
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
}

t_token	*free_mid_list(t_token *current)
{
	t_token	*next;
	t_token	*prev;

	if (current->next && current->prev)
	{
		next = current->next;
		prev = current->prev;
		next->prev = prev;
		prev->next = next;
	}
	if (!current->next && current->prev)
	{
		next = NULL;
		prev = current->prev;
		prev->next = NULL;
	}
	if (current->next && !current->prev)
	{
		next = current->next;
		next->prev = NULL;
	}
	if (!current->next && !current->prev)
		return (NULL);
	free_ptr((void **)&current->value);
	free(current);
	return (next);
}

void	*free_ptr(void **ptr)
{
	if (*ptr && ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (NULL);
}
