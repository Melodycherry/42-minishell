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

void	*free_ptr(void **ptr)
{
	if (*ptr && ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (NULL);
}

void	free_all(t_shell *shell)
{
	free_token_list(shell);
	free_tab(&shell->cmd.envp_copy);
	free_tab(&shell->cmd.envp_exp);
	free_tab(&shell->executor.av);
	free_tab(&shell->executor.paths);
	free_tab(&shell->executor.pipe_av);
	free_tab(&shell->executor.redir_av);
	free_ptr((void **)&shell->cmd.line);
	free_ptr((void **)&shell->executor.redir_file);
}
void	free_child_pipe(t_shell *shell)
{
	free_token_list(shell);
	free_tab(&shell->cmd.envp_copy);
	free_tab(&shell->executor.av);
	free_tab(&shell->executor.paths);
	free_tab(&shell->executor.redir_av);
	free_ptr((void **)&shell->cmd.line);
	free_ptr((void **)&shell->executor.redir_file);
}

void	free_child_redir(t_shell *shell)
{
	free_token_list(shell);
	free_tab(&shell->cmd.envp_copy);
	free_tab(&shell->executor.av);
	free_tab(&shell->executor.paths);
	free_tab(&shell->executor.pipe_av);
	free_ptr((void **)&shell->cmd.line);
	free_ptr((void **)&shell->executor.redir_file);
}
