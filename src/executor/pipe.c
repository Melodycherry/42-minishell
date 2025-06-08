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

void exec_pipe(t_shell *shell)
{
        (void)shell;
}

void	pipe_exist(t_shell *shell, t_token *token)
{
	while (token->next)
	{
		if(token->type == T_PIPE)
			shell->executor.pipe_exist = TRUE;
		token = token->next;
	}
}