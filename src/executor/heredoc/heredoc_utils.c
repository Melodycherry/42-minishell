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

void	nb_heredoc(t_shell *shell, t_token *token)
{
	shell->executor.nb_heredoc = 0;
	while (token->next)
	{
		if (token->type == T_HEREDOC)
			shell->executor.nb_heredoc++;
		token = token->next;
	}
}
