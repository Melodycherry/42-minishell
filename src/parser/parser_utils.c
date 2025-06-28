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

t_bool	ft_isoperator(int c)
{
	if (c == '|' || c == '>' || c == '<')
		return (TRUE);
	return (FALSE);
}

//gerer les cas d erreur a utiliser en parallele de typedef
t_bool	is_token_error(t_token *token, t_shell *shell)
{
	if (shell->tlist.token_cnt > 1)
	{
		while (token) // 2 a 6 = operateur
		{
			if (token->next)
			{
				if (token->type == 3 && token->next->type == 4)
					token = token->next;
				else if ((token->type >= 2 && token->type <= 6)
					&& (token->next->type >= 2 && token->next->type <= 6))
					return (TRUE);
			}
			token = token->next;
		}
	}
	return (FALSE);
}

void	extract_dbl_token(t_shell *shell, int *i, int *j, t_token *current)
{
	(*i) = (*i) + 2;
	create_insert_token(shell, *i, *j, current);
}

void	extract_sgl_token(t_shell *shell, int *i, int *j, t_token *current)
{
	(*i)++;
	create_insert_token(shell, *i, *j, current);
}
