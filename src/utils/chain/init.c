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

void	init_list(t_shell *shell)
{
	shell->tlist->head = NULL;
	shell->tlist->token_cnt = 0;
}

// a voir si il faudra malloc le texte ou pas, faudra demander a Pieric pcq je suis pas tant sure.
t_token	*create_token(int type, char *value)
{
	t_token *new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	ft_memset(new_token, 0, sizeof(new_token));
	new_token->value = value;
	//strdup et a a fin on free la line qui est lue par readline
	new_token->type = type;
	return (new_token);
}

// a utiliser pour la premiere mise en place des listes chainees
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

