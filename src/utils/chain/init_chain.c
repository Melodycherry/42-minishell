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
// testée a l air ok
void	init_list(t_shell *shell)
{
	shell->tlist.head = NULL;
	shell->tlist.token_cnt = 0; //n est pas mis a jour dans les fonctions
	shell->executor.is_forked = FALSE;
	shell->executor.is_forked = FALSE;
}

// creation d un token. 
// Il y a un malloc, pas oublier de free
// testée a l air ok
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
		token->next = NULL;
		token->prev = NULL;
		tlist->token_cnt = 1;
	}
	else
	{
		current = tlist->head;
		while (current->next)
			current = current->next;
		current->next = token;
		token->prev = current;
		token->next = NULL;
		tlist->token_cnt++;
	}
}
//insert un token entre 2 token et verifie et met a jour la head si besoin
// testée a l air ok
void	insert_mid_list(t_token *current, t_token *new_token, t_shell *shell)
{
	t_token	*prev;

	if (!new_token || !current)
		return ;
	if (current->prev == NULL)
	{
		new_token->prev = NULL;
		shell->tlist.head = new_token;
	}
	else
	{
		prev = current->prev;
		new_token->prev = prev;
		prev->next = new_token;
	}
	new_token->next = current;
	current->prev = new_token;
	if (shell->tlist.head == current)
		new_token = shell->tlist.head;
}

//crée avec la old fonction et appele l insertion 
//testée a l air ok
void	create_insert_token(t_shell *shell, int i, int j, t_token *current)
{
	t_token	*new_token;
	char	*value;

	value = current->value;
	current->var_value = NULL;
	new_token = create_token(T_UNKNOWN, &value[j], i - j);
	insert_mid_list(current, new_token, shell);
	shell->tlist.token_cnt++;
}
