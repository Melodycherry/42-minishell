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
		printf(" freetoklist : curr varvalue : ptr : %p varval : %s\n", current->var_value, current->var_value);
		printf(" freetoklist : curr value : ptr : %p val : %s\n", current->value, current->value);
		free_ptr((void **)&current->value);
		free_ptr((void **)&current->var_value);
		free(current);
		current = next;
	}
	shell->tlist.head = NULL;
}

// fonction pour free si un pb pendant la copie de tableau (genre envp)
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

// la meme mais pour tout le tableau
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
	free(tab);
	tab = NULL;
}

//free le current et reconnercte la liste chainee
//peut etre devoir gerer la head mais ca me semble etrange
t_token	*free_mid_list(t_token *current) // la aussi 26 lignes ca pete les couilles 
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

/**** PDEMONT A DIT QUE C EST BON ******/
/* nous rejetons toutes responsabilité, merci de vous referer directement a PDEMOUUUNT lui meme*/
void	*free_ptr(void **ptr)
{
	if (*ptr && ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (NULL);
}