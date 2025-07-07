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
			handle_redir_in(shell, shell->executor.redir_file);
		if (type == T_REDIR_OUT)
			handle_redir_out(shell, shell->executor.redir_file);
		if (type == T_REDIR_APPEND)
			handle_redir_append(shell, shell->executor.redir_file);
	}
}

void	set_redir_type(t_shell *shell, char *redir)
{
	if (ft_strcmp(redir, ">") == 0)
		shell->executor.redir_type = T_REDIR_OUT;
	if (ft_strcmp(redir, ">>") == 0)
		shell->executor.redir_type = T_REDIR_APPEND;
	if (ft_strcmp(redir, "<") == 0)
		shell->executor.redir_type = T_REDIR_IN;
}
