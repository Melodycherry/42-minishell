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

void	redir_handle(t_shell *shell)
{
	t_token_type	type;

	type = shell->executor.redir_type;
	if (shell->executor.nb_redir > 0)
	{
		if (type == T_REDIR_IN)
			handle_redir_in(shell->executor.redir_file);
		if (type == T_REDIR_OUT)
			handle_redir_out(shell->executor.redir_file);
		if (type == T_REDIR_APPEND)
			handle_redir_append(shell->executor.redir_file);
	}
}
