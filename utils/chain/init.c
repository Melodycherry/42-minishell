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
	shell->list->head = 0;
	shell->list->token_cnt = 0;
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
	new_token->type = type;
	return (new_token);
}

// a utiliser pour la premiere mise en place des listes chainees
void	insert_base_list(t_list *list, t_token *token)
{
	t_token	*current;

	if (!list || !token)
		return ;
	if (!list->head)
	{
		list->head = token;
		list->token_cnt = 1;
	}
	else
	{
		current = list->head;
		while (current->next)
			current = current->next;
		current->next = token;
		token->prev = current;
		list->token_cnt++;
	}
}

