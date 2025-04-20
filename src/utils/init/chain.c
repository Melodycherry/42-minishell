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

// initiation de listes
// pas testée
void	init_list(t_shell *shell)
{
	shell->tlist.head = NULL;
	shell->tlist.token_cnt = 0;
}

// creation d un token. 
// Il y a un malloc, pas oublier de free
// pas testée
t_token	*create_token(int type, char *value, int n)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	ft_memset(new_token, 0, sizeof(t_token)); // t_token
	new_token->value = ft_strndup(value, n);
	new_token->type = type;
	return (new_token);
}

// a utiliser pour la premiere mise en place des listes chainees
// pas testée
void	insert_base_list(t_tlist *tlist, t_token *token)
{
	t_token	*current;

	if (!tlist || !token)
		return ;
	if (!tlist->head)
	{
		tlist->head = token;
		tlist->token_cnt = 1;
	}
	else
	{
		current = tlist->head;
		while (current->next)
			current = current->next;
		current->next = token;
		token->prev = current;
		tlist->token_cnt++;
	}
}

