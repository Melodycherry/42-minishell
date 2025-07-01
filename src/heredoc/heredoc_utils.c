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
void heredoc_exit_eof(t_shell *shell, int fd)
{
	ft_putendl_fd("syntax error: unexpected end of file", STDERR_FILENO);
	close(fd);
	free_all(shell);
	exit(1);
}
void	close_and_exit(t_shell *shell, int fd)
{
	(void)shell;
	close(fd);
	free_all(shell);
	exit(0);
}